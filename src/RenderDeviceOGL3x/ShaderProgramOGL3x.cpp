#include "ACTK.h"
#include "ShaderProgramOGL3x.h"

#include "GL\glew.h"

namespace ACTK
{
	ShaderProgramOGL3x::ShaderProgramOGL3x(const std::string& vertexShaderSource, const std::string& geometryShaderSource, const std::string& fragmentShaderSource):
		m_vertexShader(nullptr),
		m_geometryShader(nullptr),
		m_fragmentShader(nullptr)
	{
		m_program = glCreateProgram();
		if(m_program == 0)
			LOG_ERROR("Could not create ShaderProgram.");

		// ToDo: Alle Shader laden und kompilieren lassen und dann zu einem Programm zusammenfügen.
		if(vertexShaderSource.length() > 0 && fragmentShaderSource.length() > 0)
		{
			LOG_INIT("Vertex and fragment shader source is viable.");
			m_vertexShader = new ShaderObjectOGL3x(GL_VERTEX_SHADER, vertexShaderSource);
			m_fragmentShader = new ShaderObjectOGL3x(GL_VERTEX_SHADER, fragmentShaderSource);

			if(m_vertexShader->IsReady() && m_fragmentShader->IsReady())
			{
				LOG_INIT("Vertex and fragment shaders are ready to be used.");
				
				//Attach Shaders.
				glAttachShader(m_program, m_vertexShader->GetShaderHandle());
				glAttachShader(m_program, m_fragmentShader->GetShaderHandle());

			} else
			{
				LOG_ERROR("Vertex and fragment shaders initialization failed.");
			}

			if(geometryShaderSource.length() > 0)
			{
				LOG_INIT("Geometry shader source is viable.");
				m_geometryShader = new ShaderObjectOGL3x(GL_VERTEX_SHADER, geometryShaderSource);

				if(m_geometryShader->IsReady())
				{
					LOG_INIT("Geometry shader is ready to be used.");
					
					//Attach Shader.
					glAttachShader(m_program, m_vertexShader->GetShaderHandle());
				} else
				{
					LOG_ERROR("Geometry shader initialization failed.");
				}
			} 
		} else
		{
			LOG_ERROR("Vertex or fragment shader source is not viable or could not be loaded.");
		}
	}

	ShaderProgramOGL3x::~ShaderProgramOGL3x()
	{
		delete m_vertexShader;
		delete m_geometryShader;
		delete m_fragmentShader;
		glDeleteProgram(m_program);
	}

	void ShaderProgramOGL3x::Bind()
	{
		glUseProgram(m_program);
	}

	unsigned int ShaderProgramOGL3x::GetPogramHandle()
	{
		return m_program;
	}

	bool ShaderProgramOGL3x::IsReady()
	{
		return m_ready;
	}

	std::string	ShaderProgramOGL3x::GetProgramInfoLog()
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