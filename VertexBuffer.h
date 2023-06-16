#pragma once

/// <summary>
/// Manages vertex array data.
/// </summary>
class VertexBuffer
{
private:
	unsigned int m_rendererID;
public:
	/// <summary>
	/// Generates the buffer through an array of data.
	/// </summary>
	/// <param name="data">array of data to be sent through the buffer</param>
	/// <param name="size">byte size of the data array</param>
	VertexBuffer(const void* data, unsigned int size);

	/// <summary>
	/// Binds the data to the GPU
	/// </summary>
	void Bind() const;

	/// <summary>
	/// Unbinds the data from the GPU
	/// </summary>
	void Unbind() const;

	~VertexBuffer();
};

