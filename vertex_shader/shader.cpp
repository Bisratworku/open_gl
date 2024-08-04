#include <glad/glad.h>
#include <GlFW/glfw3.h>
#include <iostream>
//=nb NB


void Resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void UserInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

unsigned int SC_WI = 600;
unsigned int SC_HI = 600;



const char* shaderSource = "#version 330 core \n"
"layout (location = 0) in vec3 apos; \n"
"void main() {\n"
"gl_position  = vec4(apos.x, apos.y, apos.z, 1.0); \n"
"}\n\0";

const char* fragmentShaderSource = "#version 330 core \n"
"out vec4 FragColor;\n"
"void main(){\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SC_WI, SC_HI, "Triangle", NULL, NULL);
	if (!window) {
		std::cout << "Could't create a window" << std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, Resize);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
		std::cout << "Could't initalize glad" << std::endl;
		return -1;
	}
	

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1, &shaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPLATION::FAILED\n";
	}
	
	
	unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(FragmentShader);
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPLATION::FAILED\n";
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, FragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPLATION::FAILED\n" << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(FragmentShader);
	return 0;
}