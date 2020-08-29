#pragma once

#include <GLFW/glfw3.h>
#include <string>

// Representation of a game window
class Window
{
public:
	// Constructor and destructor
	Window(const std::string &title, int width, int height);
	~Window();

	// Getter
	[[nodiscard]] inline GLFWwindow *getNativeWindow() const { return window_; }

private:
	GLFWwindow *window_;   // Native window object
	int width_;            // Width of the window in pixels, TODO: Do I need to store this?
	int height_;           // Height of the window in pixels, TODO: Do I need to store this?
};
