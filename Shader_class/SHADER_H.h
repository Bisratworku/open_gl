//=nbNB

#ifndef SHADER_H
#define SHADER_H



#include <glad/glad.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath) {
		
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vFile;
			std::stringstream fFile;
			vFile << vShaderFile.rdbuf();
			fFile << fShaderFile.rdbuf();
			
			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vFile.str();
			fragmentCode = fFile.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "Failed to Read From File\n";
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);

		int success;
		char InfoLog[600];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 600, NULL, InfoLog);
			std::cout << "Can't Compile Vertex Shader \n" << InfoLog;
		}

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 600, NULL, InfoLog);
			std::cout << "Can't Compile Fragment Shader \n" << InfoLog;
		}
		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 600, NULL, InfoLog);	
			std::cout << "Can't Link the Shaders \n" << InfoLog;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	void use() {
		glUseProgram(ID);
	}
	void setBool(const std::string& name, bool value)const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), int(value));
	}
	void setInt(const std::string& name, int value)const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()),value);
	}
	void setFloat(const std::string& name, float value)const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

};











#endif