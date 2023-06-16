#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/// <summary>
/// Encapsulates al data related to GLFW Window.
/// </summary>
class Window
{
private:
	unsigned int m_width;
	unsigned int m_height;
	const char* m_title;
	GLFWwindow* m_window;
	
public:
	/// <summary>
	/// Initializes window with GLFW Context
	/// </summary>
	/// <param name="width">Screen width</param>
	/// <param name="height">Screen height</param>
	/// <param name="screenTitle">Title bar's text shown</param>
	Window(unsigned int width, unsigned int height, const char* screenTitle);

	/// <summary>
	/// Swaps drawn buffer
	/// </summary>
	void SwapBuffers();

	/// <returns>GLFW window width</returns>
	inline int GetWidth() const 
	{ return m_width; }

	/// <returns>GLFW window height</returns>
	inline int GetHeight() const 
	{ return m_height; }

	/// <returns>GLFW window aspect ratio</returns>
	inline float GetAspectRatio() const 
	{ return (float)m_width / (float)m_height; }

	/// <returns>Pointer to the GLFW window</returns>
	inline GLFWwindow* GetWindow() 
	{ return m_window; }

	/// <returns>OpenGL version used</returns>
	inline const char* GetVersion() const
	{ return "#version 330"; }

	~Window();
};

