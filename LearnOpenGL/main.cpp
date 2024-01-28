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

	// vertice coords of triangle
	GLfloat verticies[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // upper corner
	};

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

	// reference containers for vertex array object (VAO) and vertex buffer object (VBO)
	GLuint VAO, VBO;
	
	// generate the VAO and VBO with only 1 object each, order matters
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// introduce verticies to the vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	// config the vertex attribute so opengl knows how to read the vbo
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	// enable the vertex attribute so that opengl knows how to use it
	glEnableVertexAttribArray(0);
	// bind both the vao and vbo to 0 so we don't accidentally modify them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

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

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// swap back with front buffer
		glfwSwapBuffers(window);
		// poll events
		glfwPollEvents();
	}

	// ------------------------------------------------------------------------------------- //

	// delete the objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// delete the window before exiting
	glfwDestroyWindow(window);
	// terminate glfw
	glfwTerminate();
	return 0;

}