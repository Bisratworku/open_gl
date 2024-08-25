#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int SC_WI = 800;
const int SC_HI = 800;


void resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


void UserInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == 1) {
		glfwSetWindowShouldClose(window, true);
	}
}


const char* vertex = "#version   330   core \n"
"layout(location = 0) in  vec3 apos;\n"
"void main(){\n"
"   gl_Position =  vec4(apos, 1.0);\n"
"}\n\0";

const char* fragment = "#version    330  core \n"
"out vec4 fragColor;\n"
"uniform vec4 color;\n"
"void main(){\n"
"    fragColor = color;\n"
"}\n\0";


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SC_WI, SC_HI, "Uniforms", NULL, NULL);
	if (!window) {
		std::cout << "Can't Create a Window \n";
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
		std::cout << "Failed to Initalize Glad\n";
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
		std::cout << "Failed To Compile the Vertex Shader\n" << InfoLog;
	}
	
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 600, NULL, InfoLog);
		std::cout << "Failed To Compile The Fragement Shader\n" << InfoLog;
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	float vertexes[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes),vertexes, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		UserInput(window);

		glClearColor(0.6f, 0.4f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		float time = glfwGetTime();
		float Red = (sin(time) / 2.0f) +0.5f;
		unsigned int addAttr = glGetUniformLocation(shaderProgram, "color");
		glUseProgram(shaderProgram);
		glUniform4f(addAttr, Red, 0.5f, 1.0f, 1.0f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glDeleteBuffers(1,&VBO);
	glDeleteVertexArrays(1,&VAO);
	glDeleteProgram(shaderProgram);





	glfwTerminate();


	return 0;
}