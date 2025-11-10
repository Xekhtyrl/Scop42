#pragma once
#include <vector>
#include <iostream>
#include "Shader.hpp"
#include "Includes/vml.hpp"


// class Mesh;
// std::ostream& operator<<(std::ostream& out, const Mesh& obj);
struct Vertex {
    vec3 Position;		//v
    vec3 Normal;		//vn
    vec2 TexCoords;	//vt
};

class Mesh {
    public:
        // mesh data
        std::string                 _name;
        std::vector<Vertex>			_vertices;
        std::vector<unsigned int>	_indices;
        std::string                 _materialName;
		unsigned int				VAO;

        Mesh() {VAO = VBO = EBO = 0;}
        Mesh& operator=(const Mesh& oth) {
            _vertices = oth._vertices;
            _indices = oth._indices;
            _materialName = oth._materialName;
            // std::cout << oth <<std::endl;
            // std::cout << (this) <<std::endl;
			setupMesh();
            return *this;
        }
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::string textures);
        
		~Mesh() {
			std::cout << VAO << VBO << EBO << std::endl;
			if (VAO)
				glDeleteVertexArrays(1, &VAO);
			if (VBO)
				glDeleteBuffers(1, &VBO);
			if (EBO)
				glDeleteBuffers(1, &EBO);
			std::cout << "destructor end" << std::endl;
		}
		
		void Draw(Shader &shader, Material material) {
			// Bind textures if they exist
			if (material.diffuseTex.id() != 0) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, material.diffuseTex.id());
				shader.setInt("material.diffuse", 0);
			}

			if (material.specularTex.id() != 0) {
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, material.specularTex.id());
				shader.setInt("material.specular", 1);
			}

			if (material.normalTex.id() != 0) {
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, material.normalTex.id());
				shader.setInt("material.normalMap", 2);
			}

			shader.setBool("useDiffuseMap", material.diffuseTex.id() != 0);
			shader.setBool("useSpecularMap", material.specularTex.id() != 0);
			shader.setBool("useNormalMap", material.normalTex.id() != 0);
			// Upload scalar/vec3 uniforms
			shader.setVec3("material.ambient", material.ambient);
			shader.setVec3("material.diffuseColor", material.diffuse);
			shader.setVec3("material.specularColor", material.specular);
			shader.setFloat("material.shininess", material.shininess);
			shader.setFloat("material.opacity", material.opacity);

			// Draw the mesh
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// Reset active texture (optional)
			glActiveTexture(GL_TEXTURE0);
		}

		//getters
        std::vector<Vertex> vertices() const {return _vertices;}
        std::vector<Vertex>& vertices() {return _vertices;}
        std::vector<unsigned int> indices() const {return _indices;}
        std::vector<unsigned int>& indices() {return _indices;}
        std::string materialName() const {return _materialName;}
        std::string name() const {return _name;}

		//setters
        void vertices(std::vector<Vertex> vertices) {_vertices = vertices;}
        void indices(std::vector<unsigned int> idxs) {_indices = idxs;}
        void materialName(std::string matName) {_materialName = matName;}
        void name(std::string name) {_name = name;}
    private:
        //  render data
        unsigned int VBO, EBO;

        void setupMesh() {
			std::cout << "reached setupMesh()" <<std::endl;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
		
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);  

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), 
						&_indices[0], GL_STATIC_DRAW);

			// vertex positions
			glEnableVertexAttribArray(0);	
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			// vertex normals
			glEnableVertexAttribArray(1);	
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
			// vertex texture coords
			glEnableVertexAttribArray(2);	
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

			glBindVertexArray(0);
		}
};

// std::ostream& operator<<(std::ostream& out, const Mesh& obj) {
//     out << "Mesh: " << obj.name() << std::endl;
//     out << "\tvertices: (" << obj.vertices().size() << ")\n";
//     for (std::vector<Vertex>::iterator it = obj.vertices().begin(); it != obj.vertices().end(); it++)
//         out << "\t\t" <<(*it).Position << " " << (*it).TexCoords << " " << (*it).Normal << std::endl;
//     out << "\tindices: (" << obj.indices().size() << ")\n";
//     for (std::vector<unsigned int>::iterator it = obj.indices().begin(); it != obj.indices().end(); it++)
//         out << (*it) << " ";
//     out << std::endl;
//     out << "Material name: " << obj.materialName() << std::endl;
//     return out;
// }

// void printv3(std::ostream& out =std::cout, vec3 vec = {}) {
//     out << vec[0] << " " << vec[1] << " " << vec[2] << std::endl;
// }
// void printv2(std::ostream& out =std::cout, vec2 vec = {}) {
//     out << vec[0] << " " << vec[1] << std::endl;
// }

// std::ostream& operator<<(std::ostream& out, const Mesh& obj) {
//     out << "Mesh: " << obj.name() << "\n";

//     const auto& verts = obj.vertices();   // must be const accessor returning vector<Vertex>
//     out << "\tvertices: (" << verts.size() << ")\n";

//     for (size_t i = 0; i < verts.size(); ++i) {
//         const auto &v = verts[i];
//         out << "[" << i << "] ";

//         // print position if present (expecting Vector<float> of size 3)
//         out << "pos=";
//         /* if (v.Position.size() > 0) */ printv3(out, v.Position);
//         /* else out << "(empty)"; */

//         // print texcoords if present (size > 0)
//         out << " tex=";
//         /* if (v.TexCoords.size() > 0) */ printv2(out, v.TexCoords);
//        /*  else out << "(none)"; */

//         // print normal if present
//         out << " norm=";
//         /* if (v.Normal.size() > 0) */ printv3(out, v.Normal);
//         /* else out << "(none)"; */

//         out << "\n";
//     }

//     const auto& idx = obj.indices();
//     out << "\tindices: (" << idx.size() << ")\n\t\t";
//     for (size_t i = 0; i < idx.size(); ++i) {
//         out << idx[i];
//         if (i + 1 < idx.size()) out << " ";
//     }
//     out << "\n";

//     out << "Material: " << obj.materialName() << "\n";
//     return out;
// }