#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//=nbNB

const int SC_WI = 800;
const int SC_HI = 800;

void Resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void UserInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

const char* vertex = "#version 330   core \n"
"layout(location = 0) in vec3 Apos;\n"
"void main(){\n"
"   gl_Position = vec4(Apos.x, Apos.y, Apos.z, 1.0);\n"
"}\n\0";

const char* fragment = "#version 330 core \n"
"out vec4 fragColor;\n"
"void main(){\n"
"     fragColor = vec4(0.5, 0.4, 0.3, 1.0);\n"
"}\n\0";


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SC_WI, SC_HI, "EXERSCICE_2", NULL, NULL);
	if (!window) {
		std::cout << "Unable To Create a Window\n";
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, Resize);
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
		std::cout << "Fiiled To init GLAD\n";
		return -1;
	}

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);
	
	int success;
	char InfoLog[600];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 600, NULL, InfoLog);
		std::cout << "THE Shader Did't Compile Due to -> " << InfoLog;
		return -1;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 600, NULL, InfoLog);
		std::cout << "THE FragmenT Shader DID't Compile Due to -> " << InfoLog;
		return -1;
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 600, NULL, InfoLog);
		std::cout << "Failed To LInk The Program Due To -> " << InfoLog;
		return -1;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	float first[]{
		 -0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // 
	};
	float second[] = {
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f
	};

	unsigned int VBO[2], VAO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(first), first, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(second), second, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	while (!glfwWindowShouldClose(window)) {
		UserInput(window);

		glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);

	
	}
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(2, VBO);
	glDeleteVertexArrays(2, VAO);

	glfwTerminate();

	

	return 0;
}