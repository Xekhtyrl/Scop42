#include "Shader.hpp"
#include "CreateShader.hpp"

Shader::Shader(const char* vertexCode, const char* fragmentCode)
{
	unsigned int vertex, fragment;
	
	CompileShader(vertex, vertexCode, GL_VERTEX_SHADER);
	CompileShader(fragment, fragmentCode, GL_FRAGMENT_SHADER);
	CreateShaderProgram(vertex, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::Shader(std::string vertexFilePath, std::string fragmentFilePath) {
	std::string vShaderCode, fShaderCode;
	unsigned int vertex, fragment;
	
	try {
		vShaderCode = fileToStr(vertexFilePath);
		fShaderCode = fileToStr(fragmentFilePath);
	} catch (...) {
		std::cerr << "Error: Shader constructor failed.\n";
		throw;
	}
	
	CompileShader(vertex, vShaderCode.c_str(), GL_VERTEX_SHADER);
	CompileShader(fragment, fShaderCode.c_str(), GL_FRAGMENT_SHADER);
	CreateShaderProgram(vertex, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}



void Shader::CompileShader(unsigned int& shader, const char* shaderCode, unsigned int type) {
	int success;
	char infoLog[512];
	unsigned int frag;
	
	// vertex Shader
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	// print compile errors if any
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	std::cerr << shaderCode << std::endl;
	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};
}

void Shader::CreateShaderProgram(unsigned int vertex, unsigned int fragment) {
	int success;
	char infoLog[512];
	unsigned int frag;
	
	// CompileShader(frag, CreateShader().getContent().c_str(), GL_FRAGMENT_SHADER);
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	// glAttachShader(ID, frag);
	glLinkProgram(ID);
	// print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// glDeleteShader(frag);
}

void Shader::use() 
{ 
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const
{ 
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloats(const std::string &name, float r, float g, float b, float a) const
{ 
	glUniform4f(glGetUniformLocation(ID, name.c_str()), r, g, b, a); 
}

void Shader::addShader(const char *shaderCode, unsigned int type) {
	unsigned int shader;
	int success;
	char infoLog[512];

	CompileShader(shader, shaderCode, type);
	glAttachShader(ID, shader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(shader);
}

unsigned int Shader::getID() {
	return ID;
}