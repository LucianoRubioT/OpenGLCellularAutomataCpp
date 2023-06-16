#include "Shader.h"
#include "Renderer.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& filePath) : m_filePath(filePath), m_rendererID(0)
{
	ShaderProgramSource source = ParseShader(filePath);
	m_rendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
		return m_uniformLocationCache[name];
	_glCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
	if (location == -1)
		std::cout << "Shader Warning: uniform " << name << " is not being used\n";
	m_uniformLocationCache[name] = location;
	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::ifstream stream(filepath);
	std::string line;
	std::stringstream strstream[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else strstream[(int)type] << line << '\n';
	}
	return { strstream[0].str(), strstream[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	_glCall(glShaderSource(id, 1, &src, nullptr));
	_glCall(glCompileShader(id));

	int result;
	_glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (!result)
	{
		int length;
		_glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		_glCall(glGetShaderInfoLog(id, length, &length, message));
		//ERROR MESSAGE
		std::cout << "Failed to compile" <<
			(type == GL_VERTEX_SHADER ? " vertex " : " fragment ") <<
			"shader!\n" << message << std::endl;

		_glCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	_glCall(glAttachShader(program, vs));
	_glCall(glAttachShader(program, fs));
	_glCall(glLinkProgram(program));
	_glCall(glValidateProgram(program));
	_glCall(glDeleteShader(vs));
	_glCall(glDeleteShader(fs));

	return program;
}

void Shader::Bind() const
{
	_glCall(glUseProgram(m_rendererID));
}

void Shader::Unbind() const
{
	_glCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	_glCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	_glCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform2f(const std::string& name, float a, float b)
{
	_glCall(glUniform2f(GetUniformLocation(name), a, b));
}

void Shader::SetUniform4f(const std::string& name, float a, float b, float c, float d)
{
	_glCall(glUniform4f(GetUniformLocation(name), a, b, c, d));
}

void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4& matrix)
{
	_glCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

Shader::~Shader()
{
	_glCall(glDeleteProgram(m_rendererID));
}

