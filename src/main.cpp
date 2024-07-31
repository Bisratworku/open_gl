#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <random>
//=nb  NB
#include <iostream>
unsigned int const hi = 600;
unsigned int const wi = 600;

static void resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

static void user_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(wi, hi, "Hello world", NULL, NULL);
	if (window == NULL) {
		std::cout << "Hello world" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
		std::cout << "Failed to init glad" << std::endl;
		return -1;
	}
	while (!glfwWindowShouldClose(window)){
		glfwPollEvents();
		user_input(window);
		glfwSwapBuffers(window);
	}
	//glfwTerminate();
	return 0;
}