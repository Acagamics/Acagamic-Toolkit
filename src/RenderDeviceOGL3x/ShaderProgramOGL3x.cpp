#include "ACTK.h"
#include "ShaderProgramOGL3x.h"
#include "ShaderObjectOGL3x.h"

#include "TypeConverterOGL3x.h"

#include "GL\glew.h"

namespace ACTK
{
	ShaderProgramOGL3x::ShaderProgramOGL3x(const std::string& vertexShaderSource, const std::string& geometryShaderSource, const std::string& fragmentShaderSource):
		m_vertexShader(nullptr),
		m_geometryShader(nullptr),
		m_fragmentShader(nullptr)
	{
		m_ready = false;
		m_vertexShader = ShaderObjectOGL3xPtr(new ShaderObjectOGL3x(GL_VERTEX_SHADER, vertexShaderSource));
		if (geometryShaderSource.length() > 0)
		{
			m_geometryShader = ShaderObjectOGL3xPtr(new ShaderObjectOGL3x(GL_GEOMETRY_SHADER, geometryShaderSource));
		}
		m_fragmentShader = ShaderObjectOGL3xPtr(new ShaderObjectOGL3x(GL_FRAGMENT_SHADER, fragmentShaderSource));

		m_program = glCreateProgram();
		if(m_program == 0)
			LOG_ERROR("Could not create ShaderProgram.");

		LOG_INIT("Vertex and fragment shader source is viable.");
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
		glLinkProgram(m_program);
	}

	ShaderProgramOGL3x::~ShaderProgramOGL3x()
	{
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

	std::string	ShaderProgramOGL3x::getProgramInfoLog()
	{
		char* buffer;
		GLint length, result;

		/* get the shader info log */
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
		buffer = (char*)malloc(length);

		glGetProgramInfoLog(m_program, length, &result, buffer);

		return std::string(buffer);
	}

	UniformMap ShaderProgramOGL3x::findUniforms()
	{
		int programHandle = m_program;

        int numberOfUniforms;
		glGetProgramiv(programHandle, GL_ACTIVE_UNIFORMS, &numberOfUniforms);

        int uniformNameMaxLength;
		glGetProgramiv(programHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformNameMaxLength);

		UniformMap uniforms;
		if(numberOfUniforms > 0)
			LOG_INIT("Uniforms:");

        for (unsigned int i = 0; i < (unsigned int)numberOfUniforms; ++i)
        {
            int uniformNameLength;
            int uniformSize;
            GLenum uniformType;
            GLchar* uniformName = new GLchar[uniformNameMaxLength];

            glGetActiveUniform(programHandle, i, uniformNameMaxLength, &uniformNameLength, &uniformSize, &uniformType, uniformName);

			if (strncmp(uniformName, "gl_", strlen("gl_")) == 0)
			{
                //
                // Names starting with the reserved prefix of "gl_" have a location of -1.
                //
                continue;
            }

            //
            // Skip uniforms in a named block
            //
            int uniformBlockIndex;
			glGetActiveUniformsiv(programHandle, 1, &i, GL_UNIFORM_BLOCK_INDEX, &uniformBlockIndex);

            if (uniformBlockIndex != -1)
            {
                continue;
            }

            int uniformLocation = glGetUniformLocation(programHandle, uniformName);
			
			LOG_INIT("\tName: %s, \tLocation: %d, \tArraySize: %d", uniformName, uniformLocation, uniformSize);
			// TODO: Füge die abgeleiteten Uniforms mit switch case
			//uniforms.insert(std::pair<std::string, UniformOGL3x*>(uniformName, new UniformOGL3x(uniformLocation, uniformSize, TypeConverterOGL3x::ToActiveUniformType(uniformType), this))));
			// Meins! (Grigori)

			UniformDatatype type = TypeConverterOGL3x::ToActiveUniformType(uniformType);

			switch (type)
			{
			case(UniformDatatype::Float):
			case(UniformDatatype::FloatVector2):
			case(UniformDatatype::FloatVector3):
			case(UniformDatatype::FloatVector4):
			case(UniformDatatype::FloatMatrix22):
			case(UniformDatatype::FloatMatrix23):
			case(UniformDatatype::FloatMatrix24):
			case(UniformDatatype::FloatMatrix32):
			case(UniformDatatype::FloatMatrix33):
			case(UniformDatatype::FloatMatrix34):
			case(UniformDatatype::FloatMatrix44):
				uniforms.insert(std::pair<std::string, UniformOGL3x*>(uniformName, new UniformF(uniformLocation, type, uniformSize, this)));
				break;
			case(UniformDatatype::Int):
			case(UniformDatatype::IntVector2):
			case(UniformDatatype::IntVector3):
			case(UniformDatatype::IntVector4):
				uniforms.insert(std::pair<std::string, UniformOGL3x*>(uniformName, new UniformI(uniformLocation, type, uniformSize, this)));
				break;
			}
        }
        return uniforms;
	}
}