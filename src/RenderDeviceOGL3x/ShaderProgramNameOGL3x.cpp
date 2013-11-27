#include "ACTK.h"
#include "ShaderProgramNameOGL3x.h"

#include "GL\glew.h"

namespace ACTK
{
	ShaderProgramNameOGL3x::ShaderProgramNameOGL3x() : m_program(0)
	{
		m_program = glCreateProgram();
		if(m_program == 0)
			LOG_ERROR("Could not create ShaderProgram.");
	}

	ShaderProgramNameOGL3x::~ShaderProgramNameOGL3x()
	{
		glDeleteProgram(m_program);
	}

	unsigned int ShaderProgramNameOGL3x::getHandle()
	{
		return m_program;
	}

	std::string ShaderProgramNameOGL3x::GetInfoLog()
	{
		char* buffer;
		GLint length, result;

		/* get the shader info log */
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
		buffer = (char*)malloc(length);

		glGetProgramInfoLog(m_program, length, &result, buffer);

		return std::string(buffer);
	}

}