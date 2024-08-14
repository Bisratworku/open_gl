//=nbBN
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

unsigned const int SC_WI = 800;
unsigned const int SC_HI = 800;

void resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void User_Input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}


const char* vertex = "#version  330  core \n"
"out vec3 tri2; \n"
"layout  (location = 0) in vec3 apos;\n"
"layout  (location = 0) in vec3 bpos;\n"
"void main() {\n"
"    gl_Position = vec4(apos.x, apos.y, apos.z, 1.0);\n"
"	 tri2 = vec4(bpos.x,bpos.y, bpos.z, 1.0);\n"
"}\0";


const char* fragment = "#version  330 core \n"
"out vec4 fragColor; \n"
"void main(){\n"
"    fragColor = vec4(0.5, 0.5, 0.0, 1.0);\n"
"}\n\0";


int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//********creating a window********* //
	GLFWwindow* window = glfwCreateWindow(SC_WI, SC_HI, "TRIANGLE", NULL, NULL);
	if (!window) {
		std::cout << "CAN'T CREATE THE WINDOW\n";
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, resize);
	glfwMakeContextCurrent(window);
	//************Init glad**************//
	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
		std::cout << "CAN'T INIT GLAD\n";
		return -1;
	}

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);

	int success;
	char InfoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, InfoLog);
		std::cout << "Can't Compile Shader Due To --" << InfoLog;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);
	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, InfoLog);
		std::cout << "--- Fragment Shader Couldn't Compile Due to ---" << InfoLog;
	}

	unsigned int ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vertexShader);
	glAttachShader(ShaderProgram, fragmentShader);
	glLinkProgram(ShaderProgram);
	
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ShaderProgram, 512, NULL, InfoLog);
		std::cout << "--- THE Shader Program Couldn't Compile Due to ---" << InfoLog;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float TriangleOne[] = {
		0.0f, 0.5f, 0.0f,
		0.5f,-0.5f, 0.0f,
	   -0.5f,-0.5f, 0.0f
	};
	float TriangleTwo[] = {
		0.0f, 0.8f, 0.0f,
		0.8f,-0.8f,  0.0f,
	   -0.8f,-0.8f, 0.0f 
	};

	unsigned int VBO1, VBO2, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	/*----------------------------------------------------*/
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleOne), TriangleOne, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/*------------------------------------------------------*/
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleTwo), TriangleTwo, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	/*-----------------------------------------------------*/


		
	while (!glfwWindowShouldClose(window)) {
		User_Input(window);

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glUseProgram(ShaderProgram);
		glDrawArrays(GL_TRIANGLES_ADJACENCY, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	
	
	
	
	
	glfwTerminate();

	
	return 0;
}