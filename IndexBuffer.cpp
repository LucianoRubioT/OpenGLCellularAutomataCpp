#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	_glCall(glGenBuffers(1, &m_rendererID));
	_glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	_glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
	_glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

void IndexBuffer::Unbind() const
{
	_glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

IndexBuffer::~IndexBuffer()
{
	_glCall(glDeleteBuffers(1, &m_rendererID));
}
