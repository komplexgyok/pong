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

	// Getters
	[[nodiscard]] inline GLFWwindow *getNativeWindow() const { return window_; }
	[[nodiscard]] inline int getWidth() const { return width_; }
	[[nodiscard]] inline int getHeight() const { return height_; }

private:
	GLFWwindow *window_;   // Native window object
	int width_;            // Width of the window in pixels
	int height_;           // Height of the window in pixels
};
