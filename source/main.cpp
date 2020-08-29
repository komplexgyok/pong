#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
	// Window settings
	const char*        WINDOW_TITLE  = "Pong";
	const unsigned int WINDOW_WIDTH  = 800;
	const unsigned int WINDOW_HEIGHT = 600;

	// Initialize GLFW
	if (!glfwInit()) {
		std::cout << "ERROR: Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// OpenGL 4.0+ and core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	// Window is not resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

	if (!window) {
		std::cout << "ERROR: Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR: Failed to initialize glad" << std::endl;
		return -1;
	}

	// Set the size of the rendering window
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Loop until the user closes the window
	while(!glfwWindowShouldClose(window)) {
		// Process input
		// Update
		// Render

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for I/O events (keyboard, mouse, etc.)
		glfwPollEvents();
	}

	// Clean up all allocated resources
	glfwDestroyWindow(window);
	glfwTerminate();
}
