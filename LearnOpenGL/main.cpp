/*
The main purpose of this program and all to come is to get hands-on
experience with OpenGL, GLAD, GLFW, ImGui, and creating a engine
itself. The code is overly commented intentionally in the case
I need to go back and review it.
*/

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// ------------------------------------------------------------------------------------- //

// vertice coords of triangle
GLfloat vertices[] = {
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // inner down
};

GLuint indices[] = {
	0, 3, 5, // lower left triangle
	3, 2, 4, // lower right triangle
	5, 4, 1 // upper top triangle
};

// ------------------------------------------------------------------------------------- //

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

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	while (!glfwWindowShouldClose(window)) {
		// specifiy background color, navy
		glClearColor(0.07f, 0.13f, 0.18f, 1.0f);
		// clean back buffer and assign new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// tell OpenGL which shader program we want to use
		shaderProgram.Activate();
		// bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// swap back with front buffer
		glfwSwapBuffers(window);
		// poll events
		glfwPollEvents();
	}

	// ------------------------------------------------------------------------------------- //

	// delete the objects
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// delete the window before exiting
	glfwDestroyWindow(window);
	// terminate glfw
	glfwTerminate();
	return 0;
}