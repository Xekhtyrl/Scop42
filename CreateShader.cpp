#include "CreateShader.hpp"

// Default constructor
CreateShader::CreateShader() { 
	_content.push_back("#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"    FragColor = ourColor;\n"
		"}\0");
	return; }
CreateShader::CreateShader(std::vector<float> colors) { 
	_content.push_back("#version 330 core\n");
	FragmentShader(colors);
	return;
}
CreateShader::CreateShader(int vecSize) {
	_content.push_back("#version 330 core\n");

	if (vecSize < 5)
		VertexShader(vecSize);
	else
		VertexColShader(vecSize);
	return;
}


// Copy constructor
CreateShader::CreateShader(const CreateShader &other) {
  *this = other;
  return;
}

// Copy assignment overload
CreateShader &CreateShader::operator=(const CreateShader &rhs) {
  (void)rhs;
  return *this;
}

// Default destructor
CreateShader::~CreateShader() { return; }

void CreateShader::FragmentShader(std::vector<float> colors) {
	std::string colorStr;
	for (int i = 0; i < colors.size(); i++)
		colorStr.append(floatToStr(colors[i]) + ", ");
	strTrim(colorStr, ", ");
	_content.push_back("out vec4 FragColor;\n\n");
	_content.push_back("void main()\n{\n");
	_content.push_back("\tFragColor = vec4(" + colorStr + ", 1.0f);\n");
	_content.push_back("}\0");
}

void CreateShader::VertexShader(int vecSize) {
	_content.push_back("layout (location = 0) in vec" + std::to_string(vecSize) + " aPos;\n");
	_content.push_back("void main()\n{\n");
	_content.push_back("\tgl_Position = vec" + std::to_string(vecSize + 1) + "(aPos.x, aPos.y, aPos.z, 1.0);\n");
	_content.push_back("}\0");

}

void CreateShader::VertexColShader(int vecSize) {
	int size = vecSize - 3;
	std::string sizeStr = std::to_string(size);
	_content.push_back("layout (location = 0) in vec" + sizeStr + " aPos;\n");
	_content.push_back("layout (location = 1) in vec3 aColor;\n\n"); // is color always 3 or can it be 4
	_content.push_back("out vec3 ourColor;\n\n");
	_content.push_back("void main()\n{\n");
	_content.push_back("\tgl_Position = vec" + std::to_string(size + 1) + "(aPos, 1.0);");
	_content.push_back("\tourColor = aColor;");
	_content.push_back("}\0");
}

std::string CreateShader::getContent() {
	std::string str;
	for (int i = 0; i < _content.size(); i++)
		str.append(_content[i]);
	return str;
}