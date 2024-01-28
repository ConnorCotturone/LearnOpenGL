/*
The main purpose of this program and all to come is to get hands-on
experience with OpenGL, GLAD, GLFW, ImGui, and creating a engine
itself. The code is overly commented intentionally in the case
I need to go back and review it.
*/

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {
	// initialize glfw
	glfwInit();
	// tell glfw what version of opengl we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// create the glfw window
	GLFWwindow* window = glfwCreateWindow(800, 800, "Test-Window", NULL, NULL);
	// error check the windows creation
	if (window == NULL) { 
		std::cout << "failed to create window" << std::endl; 
		glfwTerminate();
		return -1;
	}
	// make window current context
	glfwMakeContextCurrent(window);
	// load glad
	gladLoadGL();
	// specifiy viewport
	glViewport(0, 0, 800, 800);

	// ------------------------------------------------------------------------------------- //

	// vertice coords of triangle
	GLfloat verticies[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // inner down
	};

	// ------------------------------------------------------------------------------------- //

	GLuint indicies[] = {
		0, 3, 5, // lower left triangle
		3, 2, 4, // lower right triangle
		5, 4, 1 // upper top triangle
	};

	// create vertex shader object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// attach vertex shader source to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// compile the vertex shader into machine code
	glCompileShader(vertexShader);

	// repeat again for the fragment shader object
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// create shader program object, get its reference
	GLuint shaderProgram = glCreateProgram();
	// attach vertex and fragment shader to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// link all the shaders together into the shader program
	glLinkProgram(shaderProgram);
	
	// delete shaders, now useless
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ------------------------------------------------------------------------------------- //

	// reference containers for vertex array object (VAO) and vertex buffer object (VBO) and element buffer object (EBO)
	GLuint VAO, VBO, EBO;
	
	// generate the VAO and VBO with only 1 object each, order matters
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// make the vao the current vertex array object
	glBindVertexArray(VAO);
	// bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// introduce verticies to the vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	// bind the ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// introduce indicies into the ebo
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
	// config the vertex attribute so opengl knows how to read the vbo
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	// enable the vertex attribute so that opengl knows how to use it
	glEnableVertexAttribArray(0);
	// bind both the vao and vbo to 0 so we don't accidentally modify them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ------------------------------------------------------------------------------------- //

	// specifiy background color, navy
	glClearColor(0.07f, 0.13f, 0.18f, 1.0f);
	// clean back buffer and assign new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// swap back with front buffer
	glfwSwapBuffers(window);
	// while window is open
	while (!glfwWindowShouldClose(window)) {
		// specifiy background color, navy
		glClearColor(0.07f, 0.13f, 0.18f, 1.0f);
		// clean back buffer and assign new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// tell opengl which shader program to us
		glUseProgram(shaderProgram);
		// bind the vao so opengl knows to use it
		glBindVertexArray(VAO);
		// draw elements (triangles)
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// swap back with front buffer
		glfwSwapBuffers(window);
		// poll events
		glfwPollEvents();
	}

	// ------------------------------------------------------------------------------------- //

	// delete the objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	// delete the window before exiting
	glfwDestroyWindow(window);
	// terminate glfw
	glfwTerminate();
	return 0;
}