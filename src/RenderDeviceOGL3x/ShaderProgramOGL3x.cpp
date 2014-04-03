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
		LOG_DEBUG("Creating Shader Program...");
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

		if(m_vertexShader->IsReady() && m_fragmentShader->IsReady())
		{
			LOG_DEBUG("Vertex and fragment shaders are ready to be used.");
				
			//Attach Shaders.
			glAttachShader(m_program, m_vertexShader->GetShaderHandle());
			glAttachShader(m_program, m_fragmentShader->GetShaderHandle());

		} 
		else
		{
			LOG_ERROR("Vertex and fragment shaders initialization failed.");
		}

		if(geometryShaderSource.length() > 0)
		{
			LOG_DEBUG("Geometry shader source is viable.");
			if(m_geometryShader->IsReady())
			{
				LOG_DEBUG("Geometry shader is ready to be used.");
					
				//Attach Shader.
				glAttachShader(m_program, m_vertexShader->GetShaderHandle());
			} else
			{
				LOG_ERROR("Geometry shader initialization failed.");
			}
		}
		glLinkProgram(m_program);

		int linkStatus;
		glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);

		if (linkStatus == 0)
		{
			LOG_ERROR(getProgramInfoLog().c_str());
			m_ready = false;
		}
		else
		{
			LOG_DEBUG("Shader successfully  linked!");
			m_ready = true;
		}
		m_uniforms = findUniforms();
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

	void ShaderProgramOGL3x::notifyDirty(ICleanable* obj)
	{
		m_dirtyUniforms.push_front(obj);
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
			LOG_DEBUG("Uniforms:");

        for (unsigned int i = 0; i < (unsigned int)numberOfUniforms; ++i)
        {
            int uniformNameLength;
            int uniformSize;
            GLenum UniformType;
            GLchar* uniformName = new GLchar[uniformNameMaxLength];

            glGetActiveUniform(programHandle, i, uniformNameMaxLength, &uniformNameLength, &uniformSize, &UniformType, uniformName);

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
			
			LOG_DEBUG("\tName: %s, \tLocation: %d, \tArraySize: %d", uniformName, uniformLocation, uniformSize);
			// TODO: Füge die abgeleiteten Uniforms mit switch case
			// uniforms.insert(std::pair<std::string, UniformOGL3x*>(uniformName, new UniformOGL3x(uniformLocation, uniformSize, TypeConverterOGL3x::ToActiveUniformDatatype(UniformDatatype), this))));
			// Meins! (Grigori)

			UniformDatatype type = TypeConverterOGL3x::ToActiveUniformDatatype(UniformType);

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
					uniforms.insert(std::pair<std::string, IUniformOGL3x*>(uniformName, new UniformF(uniformLocation, type, uniformSize, this)));
					break;
				case(UniformDatatype::Int):
				case(UniformDatatype::IntVector2):
				case(UniformDatatype::IntVector3):
				case(UniformDatatype::IntVector4):
					uniforms.insert(std::pair<std::string, IUniformOGL3x*>(uniformName, new UniformI(uniformLocation, type, uniformSize, this)));
					break;
				case(UniformDatatype::UnsignedInt):
				case(UniformDatatype::UnsignedIntVector2):
				case(UniformDatatype::UnsignedIntVector3):
				case(UniformDatatype::UnsignedIntVector4):
					uniforms.insert(std::pair<std::string, IUniformOGL3x*>(uniformName, new UniformUI(uniformLocation, type, uniformSize, this)));
					break;
				default:
					LOG_FATAL("UniformDatatype does not exist");
					break;
			}
        }
        return uniforms;
	}

	void ShaderProgramOGL3x::setUniform(const char* name, int val)
	{
		setUniformI(name, &val, 1);
	}
	
	void ShaderProgramOGL3x::setUniform(const char* name, float val)
	{
		setUniformF(name, &val, 2);
	}

	void ShaderProgramOGL3x::setUniform(const char* name, int val1, int val2)
	{
		int val[2] = {val1,val2};
		setUniformI(name, val, 2);
	}

	void ShaderProgramOGL3x::setUniform(const char* name, float val1, float val2)
	{
		float val[2] = {val1,val2};
		setUniformF(name, val, 2);
	}

	void ShaderProgramOGL3x::setUniform(const char* name, int val1, int val2, int val3)
	{
		int val[3] = {val1,val2,val3};
		setUniformI(name, val, 3);
	}

	void ShaderProgramOGL3x::setUniform(const char* name, float val1, float val2, float val3)
	{
		float val[3] = {val1,val2,val3};
		setUniformF(name, val, 3);	
	}

	void ShaderProgramOGL3x::setUniform(const char* name, int val1, int val2, int val3, int val4)
	{
		int val[4] = {val1,val2,val3,val4};
		setUniformI(name, val, 4);
	}

	void ShaderProgramOGL3x::setUniform(const char* name, float val1, float val2, float val3, float val4)
	{
		float val[4] = {val1,val2,val3,val4};
		setUniformF(name, val, 4);	
	}
		
	void ShaderProgramOGL3x::setUniformVector(const char* name, int* val, unsigned int array_count)
	{
		setUniformI(name, val, array_count);
	}
	void ShaderProgramOGL3x::setUniformVector(const char* name, float* val, unsigned int array_count)
	{
		setUniformF(name, val, array_count);
	}

	void ShaderProgramOGL3x::setUniformMatrix(const char* name, int* val, unsigned int array_count)
	{
		setUniformI(name, val, array_count);
	}

	void ShaderProgramOGL3x::setUniformMatrix(const char* name, float* val, unsigned int array_coun)
	{
		setUniformF(name, val, array_coun);
	}

	void ShaderProgramOGL3x::setUniformI(const char* name, int* val, int arrayLength)
	{
		setUniform(name, val, ShaderProgramOGL3x::PrimitiveDatatype::Int, arrayLength);
	}

	void ShaderProgramOGL3x::setUniformF(const char* name, float* val, int arrayLength)
	{
		setUniform(name, val, ShaderProgramOGL3x::PrimitiveDatatype::Float, arrayLength);
	}

	void ShaderProgramOGL3x::setUniformUI(const char* name, unsigned int* val, int arrayLength)
	{
		setUniform(name, val, ShaderProgramOGL3x::PrimitiveDatatype::Uint, arrayLength);
	}

	void ShaderProgramOGL3x::setUniform(const char* name, void* val, PrimitiveDatatype type, int arrayLength)
	{
		auto it = m_uniforms.find( name );
		if(it != m_uniforms.end())
		{
			switch(m_uniforms[name]->Datatype)
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
					switch(type)
					{
						case(ShaderProgramOGL3x::PrimitiveDatatype::Float):
							(dynamic_cast<UniformF*>(m_uniforms[name]))->setValue( static_cast<float*>(val), arrayLength );
							break;
						case(ShaderProgramOGL3x::PrimitiveDatatype::Int):
							(dynamic_cast<UniformF*>(m_uniforms[name]))->setValue( static_cast<int*>(val), arrayLength );
							break;
						case(ShaderProgramOGL3x::PrimitiveDatatype::Uint):
							(dynamic_cast<UniformF*>(m_uniforms[name]))->setValue( static_cast<unsigned int*>(val), arrayLength );
							break;
						break;
					}
					break;
				case(UniformDatatype::Int):
				case(UniformDatatype::IntVector2):
				case(UniformDatatype::IntVector3):
				case(UniformDatatype::IntVector4):
					switch(type)
					{
						case(ShaderProgramOGL3x::PrimitiveDatatype::Float):
							(dynamic_cast<UniformI*>(m_uniforms[name]))->setValue( static_cast<float*>(val), arrayLength );
							break;
						case(ShaderProgramOGL3x::PrimitiveDatatype::Int):
							(dynamic_cast<UniformI*>(m_uniforms[name]))->setValue( static_cast<int*>(val), arrayLength );
							break;
						case(ShaderProgramOGL3x::PrimitiveDatatype::Uint):
							(dynamic_cast<UniformI*>(m_uniforms[name]))->setValue( static_cast<unsigned int*>(val), arrayLength );
							break;
						break;
					}
					break;
				case(UniformDatatype::UnsignedInt):
				case(UniformDatatype::UnsignedIntVector2):
				case(UniformDatatype::UnsignedIntVector3):
				case(UniformDatatype::UnsignedIntVector4):
					switch(type)
					{
						case(ShaderProgramOGL3x::PrimitiveDatatype::Float):
							(dynamic_cast<UniformUI*>(m_uniforms[name]))->setValue( static_cast<float*>(val), arrayLength );
							break;
						case(ShaderProgramOGL3x::PrimitiveDatatype::Int):
							(dynamic_cast<UniformUI*>(m_uniforms[name]))->setValue( static_cast<int*>(val), arrayLength );
							break;
						case(ShaderProgramOGL3x::PrimitiveDatatype::Uint):
							(dynamic_cast<UniformUI*>(m_uniforms[name]))->setValue( static_cast<unsigned int*>(val), arrayLength );
							break;
						break;
					}
					break;
				default:
					LOG_FATAL("UniformDatatype does not exist!");
					break;
			}
		}
	}
}