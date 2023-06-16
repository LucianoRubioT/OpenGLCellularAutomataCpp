#include "Renderer.h"
#include <iostream>

void _glClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool _glLogCall(const char* func, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[GL_ERROR]: " << error << "\nERROR AT: " << func
			<< "; in line " << line << "\n" << file << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear(float clearColorA, float clearColorB, float clearColorC, float clearAlpha) const
{
	_glCall(glClearColor(clearColorA, clearColorB, clearColorC, clearAlpha));
	_glCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::BindAsRenderTarget(int screenWidth, int screenHeight)
{
	_glCall(glGenFramebuffers(1, &m_frameBuffer));
	_glCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer));
	
	_glCall(glGenTextures(1, &m_fboTexture));
	_glCall(glBindTexture(GL_TEXTURE_2D, m_fboTexture));
	_glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB,
						 GL_UNSIGNED_BYTE, NULL));
	_glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	_glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	_glCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
								   m_fboTexture, 0));

	_glCall(glGenRenderbuffers(1, &m_renderBuffer));
	_glCall(glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer));
	_glCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth, screenHeight));
	_glCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer));

	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Renderer Error: BindAsRenderTarget() _" << fboStatus << "_\n";

	
	//_glCall(glViewport(0, 0, screenWidth, screenHeight));
}

void Renderer::Draw(const VertexArray& VAO, const IndexBuffer& EBO, const Shader& shader) const
{
	shader.Bind();
	VAO.Bind();
	EBO.Bind();

	_glCall(glDrawElements(GL_TRIANGLES, EBO.GetCount(), GL_UNSIGNED_INT, nullptr));
}
