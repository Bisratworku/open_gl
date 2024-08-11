//=nbNB

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

unsigned const int SC_WI = 800;
unsigned const int SC_HI = 800;

void Resize(GLFWwindow* window, int SC_WI, int SC_HI) {
	glViewport(0, 0, SC_WI, SC_HI);
}

void UserInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}


const char* vertex = "#version  330  core \n"
"layout (location = 0) in  vec3 apos; \n"
"void main() { \n"
"   gl_Position = vec4(apos.x, apos.y, apos.z, 1.0); \n"
"}\n\0";

const char* fragment = "#version 330 core \n"
"out vec4 fragColor; \n"
"void main(){\n"
"   fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); \n"
"}\n\0";



int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SC_WI, SC_HI, "Indexed_triangle", NULL, NULL);
	if (!window) {
		std::cout << "Can't Create a window\n";
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Resize);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
		std::cout << "Could't Init GLAD\n";
		return -1;
	}
	
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);

	int success;
	char InfoLog[560];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 560, NULL, InfoLog);
		std::cout << "THe shader DID'T Compile Due to  " << InfoLog;
		return -1;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);
	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 560, NULL, InfoLog);
		std::cout << "THe shader DID'T Compile Due to " << InfoLog;
	}
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 560, NULL, InfoLog);
		std::cout << "The program is NOT respondoing   " << InfoLog;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	
	float vertrexes[] = {
		0.5f, 0.5f, 0.0f,//top right 
		0.5f, -0.5f, 0.0f,//buttom right
		-0.5f, -0.5f, 0.0f,//buttom left
		-0.5f, 0.5f, 0.0f//top left
	};
	
	unsigned int indexes[]{
		0,1,3,
		1,2,3
	};
	
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertrexes), vertrexes, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		UserInput(window);

		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(shaderProgram);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		

		glfwPollEvents();
		glfwSwapBuffers(window);


	}
	

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	
	glfwTerminate();
	
	
	
	return 0;



}