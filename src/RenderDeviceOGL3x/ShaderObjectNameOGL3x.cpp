#include "ShaderObjectNameOGL3x.h"
#include "ACTK.h"
#include "GL\glew.h"

namespace ACTK
{
	ShaderObjectNameOGL3x::ShaderObjectNameOGL3x(unsigned int ShaderType)
	{
		m_shader = glCreateShader(ShaderType);
		if(m_shader == 0)
			LOG_ERROR("Could not create Shaderobject.");
	}

	ShaderObjectNameOGL3x::~ShaderObjectNameOGL3x()
	{
		glDeleteShader(m_shader);
	}

	unsigned int ShaderObjectNameOGL3x::getValue()
	{
		return m_shader;
	}

	std::string ShaderObjectNameOGL3x::GetInfoLog()
	{
		char* buffer;
		GLint length, result;

		/* get the shader info log */
		glGetProgramiv(m_shader, GL_INFO_LOG_LENGTH, &length);
		buffer = (char*)malloc(length);

		glGetProgramInfoLog(m_shader, length, &result, buffer);

		return std::string(buffer);
	}

}