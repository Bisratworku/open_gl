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

	float time = glfwGetTime();
	std::cout << "The Time is "<< time;
	
		
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