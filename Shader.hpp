#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  

class Shader
{
public:
    // the program ID
	private:
    	unsigned int ID;
		void CompileShader(unsigned int& shader, const char* shaderCode, unsigned int type);
		void CreateShaderProgram(unsigned int, unsigned int);
	public:
		// constructor reads and builds the shader
		Shader(const char* vertexCode, const char* fragmentCode);
		Shader(std::string vertexFilePath, std::string fragmentFilePath);
		// use/activate the shader
		void use();
		// utility uniform functions
		void setBool(const std::string &name, bool value) const;  
		void setInt(const std::string &name, int value) const;   
		void setFloat(const std::string &name, float value) const;
		void setFloats(const std::string &name, float r, float g, float b, float a) const;
		void setMat(const char *, const float*);
		void addShader(const char *shaderCode, unsigned int type);
		unsigned int getID();
};
  
#endif