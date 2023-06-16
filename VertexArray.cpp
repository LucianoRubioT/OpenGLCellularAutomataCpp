#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray()
{ _glCall(glGenVertexArrays(1, &m_rendererID)); }

void VertexArray::Bind() const
{ _glCall(glBindVertexArray(m_rendererID)); }

void VertexArray::Unbind() const
{ _glCall(glBindVertexArray(0)); }

void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
	Bind();
	vbo.Bind();
	const std::vector<VertexBufferElement>& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const VertexBufferElement& element = elements[i];
		_glCall(glEnableVertexAttribArray(i));
		_glCall(glVertexAttribPointer(
			i, 
			element.count, 
			element.type, 
			element.isNormalized, 
			layout.GetStride(), 
			(const void*) offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}

VertexArray::~VertexArray()
{
	_glCall(glDeleteVertexArrays(1, &m_rendererID));
}
