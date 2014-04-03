#pragma once
#include "IShaderProgram.h"
#include "ShaderObjectOGL3x.h"
#include "ICleanableObserver.h"
#include "UniformOGL3x.h"
#include <string>
#include <hash_map>

namespace ACTK
{
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

		// TODO: Funktionen definieren:
		// Die Funktionen müssen den Uniform in den richtigen Typ casten (Den Typ den er auf der Grafikkarte hat. Dafür hat jedes Objekt eine "UniformDatatype" variable. Nach der soll entschieden werden in welchen Typ gecastet wird)
		// Dann müssen die Werte gekastet werden und mit mit einer "setValue" funktion an den Uniform übergeben werden
		void setUniform(const char* name, int value);
		void setUniform(const char* name, float value);

		void setUniform(const char* name, int value1, int value2);
		void setUniform(const char* name, float value1, float value2);

		void setUniform(const char* name, int value1, int value2, int value3);
		void setUniform(const char* name, float value1, float value2, float value3);

		void setUniform(const char* name, int value1, int value2, int value3, int value4);
		void setUniform(const char* name, float value1, float value2, float value3, float value4);
		
		void setUniformVector(const char* name, int* vector, unsigned int vector_size);
		void setUniformVector(const char* name, float* vector, unsigned int vector_size);

		void setUniformMatrix(const char* name, int* matrix, unsigned int matrix_size);
		void setUniformMatrix(const char* name, float* matrix, unsigned int matrix_size);

		unsigned int GetPogramHandle();

		void Bind();
		void CleanUniforms();

		bool IsReady();

		//Diese Funktion implementieren.
		// Diese funktion fügt die Clearable zur m_dirtyUniforms-Liste hinzu
		void notifyDirty(ICleanable* obj);

	private:
		ShaderProgramOGL3x(ShaderProgramOGL3x&){}
		ShaderProgramOGL3x& operator=( const ShaderProgramOGL3x& ) {return *this;}

		void setUniformI(const char* name, int*, int arrayLength);
		void setUniformUI(const char* name, unsigned int*, int arrayLength);
		void setUniformF(const char* name, float*, int arrayLength);
		void setUniform(const char* name, void*, PrimitiveDatatype, int arrayLength);

		std::string				getProgramInfoLog();
		UniformMap				findUniforms();
		
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