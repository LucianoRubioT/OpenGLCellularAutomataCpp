#pragma once
#include "Renderer.h"

/// <summary>
/// Manages texture2D data
/// </summary>
class Texture
{
private: 
	int m_width, m_height, m_bitsPerPixel;
	unsigned int m_rendererID;
	unsigned char* m_localBuffer;
	std::string m_FilePath;
	GLuint m_frameBuffer;
	GLuint m_renderBuffer;
public:
	/// <summary>
	/// Loads an image from a directory path and generates the texture parameters and
	/// buffers.
	/// </summary>
	/// <param name="path">Directory path where the texture is found</param>
	Texture(const std::string& path);

	/// <summary>
	/// Sets buffer as the texture data. IMPORTANT: Do not use this function if the data buffer height
	/// and width is smaller than the texture's width and height. If that is the case, you'll be writing
	/// in missing data. That's why your buffer size should be determined by your texture.
	/// </summary>
	/// <param name="newBuffer">New data meant to be used</param>
	void NewBufferData(std::vector<unsigned char>* newBuffer);

	/// <summary>
	/// Binds texture buffer to GPU
	/// </summary>
	/// <param name="slot">Active buffer slot</param>
	void Bind(unsigned int slot = 0) const;

	/// <summary>
	/// Binds current texture as the render target of the GPU.
	/// </summary>
	/// <param name="attachments">Attachment to which the image from texture should be attached</param>
	void BindAsRenderTarget(GLenum attachments);

	/// <summary>
	/// Unbinds texture buffer from GPU
	/// </summary>
	void Unbind() const;
	~Texture();

	/// <returns>Texture width</returns>
	inline int GetWidth() const { return m_width; }

	/// <returns>Texture height</returns>
	inline int GetHeight() const { return m_height; }
};