#pragma once
#include "VertexBuffer.h"

class VertexBufferLayout;

/// <summary>
/// Manages buffer objects through a vertex buffer layout.
/// </summary>
class VertexArray
{
private:
	unsigned int m_rendererID;
public:
	VertexArray();

	/// <summary>
	/// Binds this vertex array to GPU
	/// </summary>
	void Bind() const;

	/// <summary>
	/// Unbinds this vertex array from the GPU
	/// </summary>
	void Unbind() const;

	/// <summary>
	/// Binds vertex array buffers through a layout
	/// </summary>
	/// <param name="vbo">Vertex buffer objects to be bound</param>
	/// <param name="layout">Layout of vertex buffer</param>
	void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);

	~VertexArray();
};

