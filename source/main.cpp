#include <GLFW/glfw3.h>
#include "Window.h"

int main()
{
	auto *window = new Window("Pong", 1280, 720);

	// Loop until the user closes the window
	while(!glfwWindowShouldClose(window->getNativeWindow())) {
		// Process input
		// Update
		// Render

		// Swap front and back buffers
		glfwSwapBuffers(window->getNativeWindow());

		// Poll for I/O events (keyboard, mouse, etc.)
		glfwPollEvents();
	}
}
