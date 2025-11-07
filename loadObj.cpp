/*
"v"
"vn"
"f"
"#"
"usemtl"
"mtlib"
"g"
"s"
*/
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

struct Face {
    std::vector<int> indices;
};
struct Mesh {
    std::string name;
    std::string material;
    std::vector<Face> faces; 
};
struct Model {
    std::string mtllib;
    std::vector <std::vector<float>> vertices;
    std::vector <std::vector<float>> normals;
    std::vector <std::vector<float>> texcoords;
    std::vector<Mesh> meshes;
};

