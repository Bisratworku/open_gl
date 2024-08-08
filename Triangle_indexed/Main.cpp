#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
//=nbNB

unsigned int SC_WI = 800;
unsigned int SC_HI = 800;

void Resize(GLFWwindow* window,int width, int height) {
	glViewport(0, 0, width, height);
}

void User_Input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

const char * vertex = "#version  330 core\n"
"layout (location = 0) in  vec3  apos;\n"
"void main() {\n"
"    gl_Position = vec4(apos.x, apos.y, apos.z, 1.0);\n"
"}\n\0"
;

const char * fragment = "#version 330 core \n"
"out vec4 fragColor;\n"
"void main() {\n"
"     fragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
"}\n\0"
;


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(SC_WI, SC_HI, "Index_Triangle", NULL, NULL);
	if (!window) {
		std::cout << "Can't create a window\n";
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Resize);
	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
		std::cout << "Can't Init glad \n";
		return -1;
	}
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "FAILD::TO::COMPILE::VERTEX::SHADER\n" << infoLog;
		return -1;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "FAILD::TO::COMPILE::FRAGMENT::SHADER\n" << infoLog;
		return -1;
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "FAILD::TO::LINK\n" << infoLog;
		return -1;
	}
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	float vertexes[] = {
		0.5f, 0.5f, 0.0f, //top right
		0.5f, -0.5f, 0.0f, //Buttom right
		-0.5, -0.5, 0.0f, //Buttom left
		-0.5f, -0.5f, 0.0f, //top left
	};
	unsigned int indexes[] = {
		0, 1, 3, //frist Tryangle
		1, 2, 3
	};
	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindVertexArray(VAO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	while (!glfwWindowShouldClose(window)) {
		User_Input(window);


		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwPollEvents();
		glfwSwapBuffers(window);
	
	}


	return 0;
}