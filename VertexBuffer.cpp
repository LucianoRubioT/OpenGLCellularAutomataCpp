#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	_glCall(glGenBuffers(1, &m_rendererID));
	_glCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	_glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{
	_glCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::Unbind() const
{
	_glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer()
{
	_glCall(glDeleteBuffers(1, &m_rendererID));
}
