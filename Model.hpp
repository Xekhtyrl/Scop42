#pragma once
#include <vector>
#include <iostream>
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Includes/vml.hpp"
#include <unordered_map>

using namespace vml;

static void parseFaceVertex(const std::string& fLine, unsigned int& vId, unsigned int& vtId, unsigned int& vnId) {
	vId = vtId = vnId = 0;

	std::stringstream ss(fLine);
	std::string val;

	if (std::getline(ss, val, '/'))
		vId = std::stoi(val);
	if (std::getline(ss, val, '/')) {
		if (val.size())
			vtId = std::stoi(val);
		if (std::getline(ss, val, '/'))
			if (val.size())
				vnId = std::stoi(val);
	}
}

// struct Textures;
struct Vertex;

// ─────────────────────────────────────────────
// Represents one material definition (.mtl)
struct Material {
    std::string name;
    vec3 ambient{1.0f};
    vec3 diffuse{1.0f};
    vec3 specular{1.0f};
    float shininess = 32.0f;
    float opacity = 1.0f;

    std::string mapKdPath; // diffuse texture file path
    std::string mapKsPath; // specular texture
    std::string mapBumpPath; // normal/bump map

    Texture diffuseTex;
    Texture specularTex;
    Texture normalTex;
};

class Model 
{
    public:
		Model() {};
        Model(char *path)
        {
			try {
				loadModel(path);
			}
			catch(std::exception &e) {
				throw;
			}
        }
		Model& operator=(const Model& oth) {
			if (this != &oth) {
				meshes = oth.meshes;
				materials = oth.materials;
				directory = oth.directory;
				_name = oth._name;
			}
			return *this;
		}
        void Draw(Shader &shader) {
			for (Mesh& x : meshes)
				x.Draw(shader, materials[x.materialName()]);
		}	
    private:
        // model data
        std::vector<Mesh> meshes;
        std::unordered_map<std::string, Material> materials;
        std::string directory;
		std::string _name;

        void loadModel(std::string path) {
            if (!validObjPath(path))
                throw std::runtime_error("Error: Invalid file name/extension.");

            std::ifstream file(path);
            if (!file.is_open())
                throw std::runtime_error("Error: Object File could not be opened or does not exist.");
            
            std::vector<vec3> temp_v;
            std::vector<vec3> temp_vn;
            std::vector<vec2> temp_vt;
			float x, y, z;
			Mesh currentMesh;

			directory = path.substr(0, path.find_last_of("/"));
            meshes.clear();
            materials.clear();

            std::string tmp;
            while (getline(file, tmp)) {
                std::stringstream ss(tmp);
				std::string type;
				ss >> type;

                if (tmp.empty() || type == "#")
                    continue;
                if (type == "vt") {
                    ss >> x >> y;
					temp_vt.push_back({x, y});
                }
                else if (type == "vn") {
                    ss >> x >> y >> z;
					temp_vn.push_back({x,y,z});
                }
                else if (type == "v") {
                    ss >> x >> y >> z;
					temp_v.push_back({x,y,z});
                }
                else if (type == "f"){
					std::string fLine;
					while (ss >> fLine) {
						unsigned int vId, vtId, vnId;
						parseFaceVertex(fLine, vId, vtId, vnId);

						Vertex vert;
						if (vId > 0)
							vert.Position = temp_v[vId - 1];
						if (vtId > 0)
							vert.TexCoords = temp_vt[vtId - 1];
						if (vnId > 0)
							vert.Normal = temp_vn[vnId - 1];
						currentMesh.vertices().push_back(vert);
						currentMesh.indices().push_back(currentMesh.indices().size()); // duplicate vertex are not handled, is it neede to do it?
					}
				}
				else if (tmp.find("g") == 0) {
					if (!currentMesh.vertices().empty()) {
						// std::cout << currentMesh <<std::endl;
						meshes.push_back(currentMesh);
						currentMesh = Mesh();
					}
					std::string name;
					ss >> name;
					currentMesh.name(name);

				}
                else if (type == "o")
					ss >> _name;
                else if (type == "usemtl") {
					std::string matName;
					ss >> matName;
					if (materials.count(matName) == 0){
						file.close();
						throw std::runtime_error("Error: Materia not found in .mtl file.");
					}
					currentMesh.materialName(matName);
				}
                else if (type == "mtlib") {
					std::string mtlpath;
					ss >> mtlpath;
					try {
						loadMtl(mtlpath);
					}
					catch(std::exception& e) {
						throw;
					}
				}
            }
			if (!currentMesh.vertices().empty()){
				// std::cout << currentMesh <<std::endl;
				meshes.push_back(currentMesh);
			}
        }
        void loadMtl(std::string path) {
			std::ifstream file(directory + path);
			if (!file.is_open())
                throw std::runtime_error("Error: Material File could not be opened or does not exist.");
			std::string line;
			Material currentMaterial;
			float x,y,z;

			while (getline(file, line)) {
				std::stringstream ss(line);
				std::string type;
				ss >> type;

				if (type == "newmtl"){
					if (!currentMaterial.name.empty())
						materials[currentMaterial.name] = currentMaterial; // store previous
					currentMaterial = Material(); // reset
					ss >> currentMaterial.name;
				}
				else if (type == "Ka"){
					ss >> x >> y >> z;
					currentMaterial.ambient = vec3{x, y, z};
				}
				else if (type == "Kd"){
					ss >> x >> y >> z;
					currentMaterial.diffuse = vec3{x, y, z};
				}
				else if (type == "Ks"){
					ss >> x >> y >> z;
					currentMaterial.specular = vec3{x, y, z};
				}
				else if (type == "Ns")
					ss >> currentMaterial.shininess;
				else if (type == "d" || type == "Tr")
					ss >> currentMaterial.opacity;
				else if (type == "mapKd")
					ss >> currentMaterial.mapKdPath;
				else if (type == "mapKs")
					ss >> currentMaterial.mapKsPath;
				else if (type == "map_Bump" || type == "bump")
					ss >> currentMaterial.mapBumpPath;
			}
			if (!currentMaterial.name.empty())
				materials[currentMaterial.name] = currentMaterial;

			file.close();

			// Load textures
			for (auto& [name, mat] : materials) {
				if (!mat.mapKdPath.empty())
					mat.diffuseTex = Texture(directory + mat.mapKdPath.c_str());
				if (!mat.mapKsPath.empty())
					mat.specularTex = Texture(directory + mat.mapKsPath.c_str());
				if (!mat.mapBumpPath.empty())
					mat.normalTex = Texture(directory + mat.mapBumpPath.c_str());
			}
		}
        // void processNode(aiNode *node, const aiScene *scene);
        // Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        // std::vector<Textures> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
        //                    std::string typeName);
        bool validObjPath(std::string path) {
            if (path.find(".obj", path.size() - 5) > path.size()){
				return false;
			}
            if (path.size() < 5){
				return false;
			}
            return true;
        }

};
