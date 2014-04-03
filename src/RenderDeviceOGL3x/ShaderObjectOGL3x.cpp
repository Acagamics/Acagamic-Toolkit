#include "ACTK.h"
#include "ShaderObjectOGL3x.h"
#include "GL\glew.h"

namespace ACTK
{
	ShaderObjectOGL3x::ShaderObjectOGL3x(GLenum shaderType, const std::string& source)
	{
		int i = 1;
		/* create shader object, set the source, and compile */
		m_shaderObject = glCreateShader(shaderType); // Hier ein Fehler den ich nicht verstehe.

		m_result = GL_FALSE;

		GLint length = strlen(source.c_str());
		const GLchar* c_source = source.c_str();
		if (m_shaderObject) 
		{
			glShaderSource(m_shaderObject, 1, &c_source, &length);
			glCompileShader(m_shaderObject);
			glGetShaderiv(m_shaderObject, GL_COMPILE_STATUS, &m_result);
			// Check if compiled.
			if (m_result) 
			{
				m_result = GL_TRUE;
			}
			else
				LOG_ERROR(this->GetCompileLog().c_str());
			}
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