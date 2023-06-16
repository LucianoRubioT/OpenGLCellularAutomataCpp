#include "Window.h"
#include <iostream>
#include "Renderer.h"

Window::Window(unsigned int width, unsigned int height, const char* screenTitle) : m_width(width), m_height(height), m_title(screenTitle)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_height, m_width, m_title, NULL, NULL);
	if(m_window == NULL) std::cout << "[GLFW] Failed to initialize window\n";

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);
	GLenum error = glewInit();
	if (error != GLEW_OK)	std::cout << "[GLEW] Failed to initialize glew\n";
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

Window::~Window()
{
	glfwTerminate();
	glfwDestroyWindow(m_window);
}