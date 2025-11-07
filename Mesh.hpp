#pragma once
#include <vector>
#include <iostream>
#include "Shader.hpp"
#include "Vector.hpp"
#include "my_glm.h"


// class Mesh;
// std::ostream& operator<<(std::ostream& out, const Mesh& obj);
struct Vertex {
    my_glm::vec3 Position;		//v
    my_glm::vec3 Normal;		//vn
    my_glm::vec2 TexCoords;	//vt
};

class Mesh {
    public:
        // mesh data
        std::string                 _name;
        std::vector<Vertex>			_vertices;
        std::vector<unsigned int>	_indices;
        std::string                 _materialName;
		unsigned int				VAO;

        Mesh() {}
        Mesh& operator=(const Mesh& oth) {
            _vertices = oth._vertices;
            _indices = oth._indices;
            _materialName = oth._materialName;
            // std::cout << oth <<std::endl;
            // std::cout << (this) <<std::endl;
            return *this;
        }
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::string textures);
        void Draw(Shader &shader);
        std::vector<Vertex> vertices() const {return _vertices;}
        std::vector<Vertex>& vertices() {return _vertices;}
        std::vector<unsigned int> indices() const {return _indices;}
        std::vector<unsigned int>& indices() {return _indices;}
        std::string materialName() const {return _materialName;}
        std::string name() const {return _name;}
        void vertices(std::vector<Vertex> vertices) {_vertices = vertices;}
        void indices(std::vector<unsigned int> idxs) {_indices = idxs;}
        void materialName(std::string matName) {_materialName = matName;}
        void name(std::string name) {_name = name;}
    private:
        //  render data
        unsigned int VBO, EBO;

        void setupMesh();
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

void printv3(std::ostream& out =std::cout, my_glm::vec3 vec = {}) {
    out << vec.x << " " << vec.y << " " << vec.z << std::endl;
}
void printv2(std::ostream& out =std::cout, my_glm::vec2 vec = {}) {
    out << vec.x << " " << vec.y << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Mesh& obj) {
    out << "Mesh: " << obj.name() << "\n";

    const auto& verts = obj.vertices();   // must be const accessor returning vector<Vertex>
    out << "\tvertices: (" << verts.size() << ")\n";

    for (size_t i = 0; i < verts.size(); ++i) {
        const auto &v = verts[i];
        out << "[" << i << "] ";

        // print position if present (expecting Vector<float> of size 3)
        out << "pos=";
        /* if (v.Position.size() > 0) */ printv3(out, v.Position);
        /* else out << "(empty)"; */

        // print texcoords if present (size > 0)
        out << " tex=";
        /* if (v.TexCoords.size() > 0) */ printv2(out, v.TexCoords);
       /*  else out << "(none)"; */

        // print normal if present
        out << " norm=";
        /* if (v.Normal.size() > 0) */ printv3(out, v.Normal);
        /* else out << "(none)"; */

        out << "\n";
    }

    const auto& idx = obj.indices();
    out << "\tindices: (" << idx.size() << ")\n\t\t";
    for (size_t i = 0; i < idx.size(); ++i) {
        out << idx[i];
        if (i + 1 < idx.size()) out << " ";
    }
    out << "\n";

    out << "Material: " << obj.materialName() << "\n";
    return out;
}