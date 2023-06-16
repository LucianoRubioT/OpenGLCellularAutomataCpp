#pragma once
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include <gl/glew.h>

/* Macro that controls OpenGL error management throughout the project.
*  ASSERT() can be used to force a break on the program when called.
*  _glCall() should be called in each GLEW function called where errors
*  could be expected. It will output an error message describing the 
*  OpenGL exception. */
#define ASSERT(x) if (!(x)) __debugbreak();
#define _glCall(x) _glClearError(); x; ASSERT(_glLogCall(#x, __FILE__, __LINE__));
void _glClearError();
bool _glLogCall(const char* func, const char* file, int line);

/// <summary>
/// Manages rendering process
/// </summary>
class Renderer
{
private:
	GLuint m_frameBuffer;
	GLuint m_fboTexture;
	GLuint m_renderBuffer;
public:
	Renderer() : m_frameBuffer(0), m_fboTexture(0), m_renderBuffer(0) {}

	/// <summary>
	/// Clears screen buffer on call using a given color.
	/// </summary>
	/// <param name="clearColorA">Red</param>
	/// <param name="clearColorB">Green</param>
	/// <param name="clearColorC">Blue</param>
	/// <param name="clearAlpha">Alpha</param>
	void Clear(float clearColorA, float clearColorB, float clearColorC, float clearAlpha) const;
	void BindAsRenderTarget(int screenWidth, int screenHeight);
	/// <summary>
	/// Draws geometry through shaders
	/// </summary>
	/// <param name="VAO">Vertex array object reference</param>
	/// <param name="EBO">Element buffer object reference</param>
	/// <param name="shader">Shader reference</param>
	void Draw(const VertexArray& VAO, const IndexBuffer& EBO, const Shader& shader) const;
};