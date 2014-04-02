#pragma once
#include <memory>

namespace ACTK
{
	class IShaderProgram
	{
	public:
		virtual ~IShaderProgram(){}

		virtual void setUniform(const char* name, int value) = 0;
		virtual void setUniform(const char* name, float value) = 0;

		virtual void setUniform(const char* name, int value1, int value2) = 0;
		virtual void setUniform(const char* name, float value1, float value2) = 0;

		virtual void setUniform(const char* name, int value1, int value2, int value3) = 0;
		virtual void setUniform(const char* name, float value1, float value2, float value3) = 0;

		virtual void setUniform(const char* name, int value1, int value2, int value3, int value4) = 0;
		virtual void setUniform(const char* name, float value1, float value2, float value3, float value4) = 0;
		
		virtual void setUniformVector(const char* name, int* vector, unsigned int vector_size) = 0;
		virtual void setUniformVector(const char* name, float* vector, unsigned int vector_size) = 0;

		virtual void setUniformMatrix(const char* name, int* matrix, unsigned int matrix_size) = 0;
		virtual void setUniformMatrix(const char* name, float* matrix, unsigned int matrix_size) = 0;
	};

	typedef std::shared_ptr<IShaderProgram> ShaderProgramPtr;
}