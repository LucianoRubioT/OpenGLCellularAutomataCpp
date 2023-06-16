#pragma once

#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

/// <summary>
/// Structure that contains shader files separately
/// </summary>
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

/// <summary>
/// Manages shader files, their compiling and usage.
/// </summary>
class Shader
{
private:
	std::string m_filePath;
	std::unordered_map<std::string, int> m_uniformLocationCache;
	unsigned int m_rendererID;

	/// <summary>
	/// Gets the identificator of a uniform based on its name
	/// </summary>
	/// <param name="name">Name of uniform to be found</param>
	/// <returns>ID of uniform requested</returns>
	int GetUniformLocation(const std::string& name);

	/// <summary>
	/// Loads shader file and divides all the different shader programs in
	/// their respective compilable format.
	/// </summary>
	/// <param name="filepath">Location of .shader file</param>
	/// <returns>Structure containing parsed shaders</returns>
	ShaderProgramSource ParseShader(const std::string& filepath);

	/// <summary>
	/// Compiles specific shader type on program.
	/// </summary>
	/// <param name="type">Shader program identifier</param>
	/// <param name="source">Shader source code</param>
	/// <returns>Generated shader's ID</returns>
	unsigned int CompileShader(unsigned int type, const std::string& source);

	/// <summary>
	/// Loads vertex and fragment shader to the GPU.
	/// </summary>
	/// <param name="vertexShader">Vertex shader source code</param>
	/// <param name="fragmentShader">Fragment shader source code</param>
	/// <returns>Generated program</returns>
	int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
public:
	Shader(const std::string& filePath);

	void Bind() const;
	void Unbind() const;

	/// <summary> Creates a uniform of type integer usable on shader programs </summary>
	void SetUniform1i(const std::string& name, int value);
	/// <summary> Creates a uniform of type float usable on shader programs </summary>
	void SetUniform1f(const std::string& name, float value);
	/// <summary> Creates a uniform of type Vec2 float usable on shader programs </summary>
	void SetUniform2f(const std::string& name, float a, float b);
	/// <summary> Creates a uniform of type Vec4 float usable on shader programs </summary>
	void SetUniform4f(const std::string& name,float a, float b, float c, float d);
	/// <summary> Creates a uniform of type Mat4 float usable on shader programs </summary>
	void SetUniformMatrix4fv(const std::string& name, glm::mat4& matrix);

	~Shader();
};