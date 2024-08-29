#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SHADER_H.h>
#include <iostream>

const int SC_WI = 900;
const int SC_HI = 900;

void Resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void UserInput(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ENTER)){
		glfwSetWindowShouldClose(window, 1);
	
	}
}



int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SC_WI, SC_HI, "TEXTURE", NULL, NULL);
	if (!window) {
		std::cout << "I Can't Create A window I just Can't I am Sorryyyyyyyy\n";
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Resize);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
		std::cout << "I can't Init GLAD \n";
	}
	float vertices[] = {
		0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f, // top right
		0.5f,-0.5f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // bottom right
	   -0.5f,-0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, // bottom left
	   -0.5f, 0.5f, 0.0f,    1.0f, 1.0f, 0.0f,    0.0f, 1.0f // top left
	};
	int indexes[] = {
		0,1,3,
		1,2,3
	};

	int  width, height, channels;
	unsigned char* img = stbi_load("C:\\Users\\bisra\\OneDrive\\Desktop\\download.jpg", &width, &height, &channels, 0);


	unsigned int VAO, VBO, EBO, TEX;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

	glGenTextures(1, &TEX);
	glBindTexture(GL_TEXTURE_2D, TEX);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (img) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "GO FUCK Your Self\n";
	}
	stbi_image_free(img);
	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Shader shaderProgram("Vertex.vs", "Fragment.fs");

	while (!glfwWindowShouldClose(window)) {
		UserInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, TEX);
		shaderProgram.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	glDeleteBuffers(1,&EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &TEX);

	glfwTerminate();


	return 0;
}
