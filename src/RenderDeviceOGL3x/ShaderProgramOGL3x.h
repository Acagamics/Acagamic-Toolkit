#pragma once
#include "IShaderProgram.h"
#include "ShaderObjectOGL3x.h"
#include "ICleanableObserver.h"
#include "UniformOGL3x.h"
#include <string>
#include <hash_map>

namespace ACTK
{
	using namespace Core;
	using namespace Renderer;

	class ShaderProgramOGL3x : public IShaderProgram, public ICleanableObserver
	{
		enum class PrimitiveDatatype : char
		{
			Int=0,
			Float,
			Uint
		};

	public:
		ShaderProgramOGL3x(const std::string& vertexShaderSource, const std::string& geometryShaderSource, const std::string& fragmentShaderSource);
		~ShaderProgramOGL3x();

		void VSetUniform(const char* name, int value);
		void VSetUniform(const char* name, float value);

		void VSetUniform(const char* name, int value1, int value2);
		void VSetUniform(const char* name, float value1, float value2);

		void VSetUniform(const char* name, int value1, int value2, int value3);
		void VSetUniform(const char* name, float value1, float value2, float value3);

		void VSetUniform(const char* name, int value1, int value2, int value3, int value4);
		void VSetUniform(const char* name, float value1, float value2, float value3, float value4);
		
		void VSetUniformVector(const char* name, int* vector, unsigned int vector_size);
		void VSetUniformVector(const char* name, float* vector, unsigned int vector_size);

		void VSetUniformMatrix(const char* name, int* matrix, unsigned int matrix_size);
		void VSetUniformMatrix(const char* name, float* matrix, unsigned int matrix_size);

		unsigned int GetPogramHandle();

		void Bind();
		void CleanUniforms();

		bool IsReady();

		//Diese Funktion implementieren.
		// Diese funktion fügt die Clearable zur m_dirtyUniforms-Liste hinzu
		void NotifyDirty(ICleanable* obj);

	private:
		ShaderProgramOGL3x(ShaderProgramOGL3x&){}
		ShaderProgramOGL3x& operator=( const ShaderProgramOGL3x& ) {return *this;}

		void SetUniformI(const char* name, int*, int arrayLength);
		void SetUniformUI(const char* name, unsigned int*, int arrayLength);
		void SetUniformF(const char* name, float*, int arrayLength);
		void SetUniform(const char* name, void*, PrimitiveDatatype, int arrayLength);

		std::string				GetProgramInfoLog();
		UniformMap				FindUniforms();
		
		UniformMap				m_uniforms;
		std::list<ICleanable*>	m_dirtyUniforms;

		unsigned int			m_program;

		ShaderObjectOGL3xPtr	m_vertexShader;
		ShaderObjectOGL3xPtr	m_geometryShader;
		ShaderObjectOGL3xPtr	m_fragmentShader;

		bool m_ready;
	};

	typedef std::shared_ptr<ShaderProgramOGL3x> ShaderProgramOGL3xPtr;
}