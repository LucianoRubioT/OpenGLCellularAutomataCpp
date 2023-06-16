#include "Texture.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string& path) : m_rendererID(0), m_FilePath(path),
m_localBuffer(nullptr), m_width(0), m_height(0), m_bitsPerPixel(0), m_frameBuffer(0),
m_renderBuffer(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);

	_glCall(glGenTextures(1, &m_rendererID));
	_glCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
	_glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	_glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	_glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	_glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	_glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));

	if (m_localBuffer)	stbi_image_free(m_localBuffer);
}

void Texture::NewBufferData(std::vector<unsigned char>* newBuffer)
{
	m_localBuffer = newBuffer->data();

	_glCall(glGenTextures(1, &m_rendererID));
	_glCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
	_glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	_glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	_glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	_glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	_glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, m_localBuffer));
}

void Texture::Bind(unsigned int slot) const
{
	_glCall(glActiveTexture(GL_TEXTURE0 + slot));
	_glCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::BindAsRenderTarget(GLenum attachments)
{
	if (attachments == GL_NONE) return;

	_glCall(glGenFramebuffers(1, &m_frameBuffer));
	_glCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_frameBuffer));
	_glCall(glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachments, GL_TEXTURE_2D, m_rendererID, 0));
	
	_glCall(glGenRenderbuffers(1, &m_renderBuffer));
	_glCall(glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer));
	_glCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height));
	_glCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer))

	GLenum DrawBuffers[1] = { attachments };
	_glCall(glDrawBuffers(1, DrawBuffers));
	if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR AT CREATING RENDER TARGET At Texture::BindAsRenderTarget()\n";

	_glCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_frameBuffer));
	_glCall(glViewport(0, 0, m_width, m_height));
}

void Texture::Unbind() const
{
	_glCall(glBindTexture(GL_TEXTURE_2D, 0));
	_glCall(glDeleteTextures(1, &m_rendererID));
}

Texture::~Texture()
{
	_glCall(glDeleteTextures(1, &m_rendererID));
	if (m_frameBuffer) _glCall(glDeleteFramebuffers(1, &m_frameBuffer));
	if (m_renderBuffer) _glCall(glDeleteRenderbuffers(1, &m_renderBuffer));
}
