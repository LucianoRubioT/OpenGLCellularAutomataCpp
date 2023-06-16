#pragma once
#include <vector>
#include <gl/glew.h>
#include "Renderer.h"

/// <summary>
/// Data structure that manages OpenGL types meant for the vertex layout used.
/// </summary>
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char isNormalized;
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

/// <summary>
/// Determines the layout of vertex buffers based on their data type size.
/// </summary>
class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;	
public:
	VertexBufferLayout() : m_stride(0) {}

	/// <summary>
	/// Template. Push type vertex to layout
	/// </summary>
	template<typename T> void Push(unsigned int count)
	{ 
		static_assert(true);
	}
	
	/// <summary>
	/// Push float type vertex to layout
	/// </summary>
	/// <param name="count">Amount of elements of type</param>
	template<> void Push<float>(unsigned int count)
	{
		m_elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	/// <summary>
	/// Push int type vertex to layout
	/// </summary>
	/// <param name="count">Amount of elements of type</param>
	template<> void Push<unsigned int>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	/// <summary>
	/// Push char type vertex to layout
	/// </summary>
	/// <param name="count">Amount of elements of type</param>
	template<> void Push<unsigned char>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	/// <returns>Vector containing all the current layout elements</returns>
	inline const std::vector<VertexBufferElement> GetElements() const
	{ return m_elements; }

	/// <returns>Byte offset between consecutive layout elements</returns>
	inline unsigned int GetStride() const { return m_stride; }
};

