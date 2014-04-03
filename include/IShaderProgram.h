#pragma once
#include <memory>

namespace ACTK
{
namespace Renderer
{
	class IShaderProgram
	{
	public:
		virtual ~IShaderProgram(){}

		virtual void VSetUniform(const char* name, int value) = 0;
		virtual void VSetUniform(const char* name, float value) = 0;

		virtual void VSetUniform(const char* name, int value1, int value2) = 0;
		virtual void VSetUniform(const char* name, float value1, float value2) = 0;

		virtual void VSetUniform(const char* name, int value1, int value2, int value3) = 0;
		virtual void VSetUniform(const char* name, float value1, float value2, float value3) = 0;

		virtual void VSetUniform(const char* name, int value1, int value2, int value3, int value4) = 0;
		virtual void VSetUniform(const char* name, float value1, float value2, float value3, float value4) = 0;
		
		virtual void VSetUniformVector(const char* name, int* vector, unsigned int vector_size) = 0;
		virtual void VSetUniformVector(const char* name, float* vector, unsigned int vector_size) = 0;

		virtual void VSetUniformMatrix(const char* name, int* matrix, unsigned int matrix_size) = 0;
		virtual void VSetUniformMatrix(const char* name, float* matrix, unsigned int matrix_size) = 0;
	};

	typedef std::shared_ptr<IShaderProgram> ShaderProgramPtr;
}}