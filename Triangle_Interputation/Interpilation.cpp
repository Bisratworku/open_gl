//=nbNB
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int SC_WI = 800;
const int SC_HI = 800;

void resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void UserInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}


const char * vertex = "#version  330 core \n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec4 frag;\n"
"void main(){\n"
"  gl_Position = vec4(position, 1.0);\n"
"  frag = vec4(color, 1.0);\n"
"}\0\n";

const char* fragment = "#version  330 core \n"
"in vec4 frag;\n"
"out vec4 fragColor;\n"
"void main(){\n"
"    fragColor = frag;\n"
"}\0\n";


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(SC_WI, SC_HI, "Interpolation", NULL, NULL);
	if (!window) {
			std::cout << "Can't Create Window\n";
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
		std::cout << "Can't Init GLAD\n";
	}
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[600];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 600, NULL, infoLog);
		std::cout << "Shader Failed To Compile\n" << infoLog;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 600, NULL, infoLog);
		std::cout << "Fragment shader Failed to Compile\n" << infoLog;
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 600, NULL, infoLog);
		std::cout << "THe program Did't link\n" << infoLog;
	}

	float vertexes[]{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(1);
	while (!glfwWindowShouldClose(window)) {
		UserInput(window);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glfwTerminate();

	return 0;
}