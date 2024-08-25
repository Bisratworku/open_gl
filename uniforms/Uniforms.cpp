#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int SC_WI = 800;
const int SC_HI = 800;


void resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


void UserInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == true) {
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
	
	/*	while (!glfwWindowShouldClose(window)) {
		UserInput(window);

		glClearColor(0.6, 0.4, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
*/






	glfwTerminate();


	return 0;
}