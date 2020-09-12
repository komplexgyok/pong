#include <glad/glad.h>
#include <stdexcept>
#include "Window.h"

/***********************************************************************************************************************
 * Constructor.
 * It sets up a window with an OpenGL context.
 *
 * @param const std::string &title   Title of the window.
 * @param int width                  Width of the window in pixels.
 * @param int height                 Height of the window in pixels.
 **********************************************************************************************************************/
Window::Window(const std::string &title, int width, int height)
	: window_ {nullptr}
	, width_ {width}
	, height_ {height}
{
	// Initialize GLFW
	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW");
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
	window_ = glfwCreateWindow(width_, height_, title.c_str(), nullptr, nullptr);

	if (!window_) {
		throw std::runtime_error("Failed to create GLFW window");
	}

	// Make the window's context current
	glfwMakeContextCurrent(window_);

	// Load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize glad");
	}

	// Set the size of the rendering window
	glViewport(0, 0, width_, height_);

	// Enable color blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/***********************************************************************************************************************
 * Destructor.
 * It cleans up all allocated resources.
 **********************************************************************************************************************/
Window::~Window()
{
	glfwDestroyWindow(window_);
	glfwTerminate();
}
