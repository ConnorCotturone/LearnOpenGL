/*
The main purpose of this program and all to come is to get hands-on
experience with OpenGL, GLAD, GLFW, ImGui, and creating a engine
itself. The code is overly commented intentionally in the case
I need to go back and review it.
*/

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	// specifiy background color, navy
	glClearColor(0.07f, 0.13f, 0.18f, 1.0f);
	// clean back buffer and assign new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// swap back with front buffer
	glfwSwapBuffers(window);
	// while window is open
	while (!glfwWindowShouldClose(window)) {
		// poll events
		glfwPollEvents();
	}
	// delete the window before exiting
	glfwDestroyWindow(window);
	// terminate glfw
	glfwTerminate();
	return 0;
}