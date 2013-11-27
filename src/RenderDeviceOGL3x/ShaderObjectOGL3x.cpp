#include "ShaderObjectOGL3x.h"
#include <GL\glew.h>

namespace ACTK
{
	ShaderObjectOGL3x::ShaderObjectOGL3x(GLenum shaderType, const std::string& source)
	{
		/* create shader object, set the source, and compile */
		m_shaderObject = glCreateShader(shaderType);

		// ToDo: Shader laden und Kompilieren und Ergebnis ausgeben
		// mit einer wunderschönen fehlerausgabe
	}

	ShaderObjectOGL3x::~ShaderObjectOGL3x()
	{
		glDeleteShader(m_shaderObject);
	}

	unsigned int ShaderObjectOGL3x::GetShaderHandle()
	{
		return m_shaderObject;
	}

	bool ShaderObjectOGL3x::IsReady()
	{
		return m_result != GL_FALSE;
	}

	std::string ShaderObjectOGL3x::GetCompileLog()
	{
		char* buffer;
		GLint length, result;

		/* get the shader info log */
		glGetShaderiv(m_shaderObject, GL_INFO_LOG_LENGTH, &length);
		buffer = (char*)malloc(length);

		glGetShaderInfoLog(m_shaderObject, length, &result, buffer);

		return std::string(buffer);
	}
}