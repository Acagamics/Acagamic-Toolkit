#pragma once
#include "IShaderProgram.h"
#include "ShaderObjectOGL3x.h"
#include "ICleanableObserver.h"
#include "UniformOGL3x.h"
#include <string>
#include <hash_map>

namespace ACTK
{
	typedef std::hash_map<std::string, IUniformOGL3x*> UniformMap;

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
		void setUniformI(const char* name, int);
		void setUniformF(const char* name, float);
		void setUniformI(const char* name, int, int);
		void setUniformF(const char* name, float, float);
		void setUniformI(const char* name, int, int, int);
		void setUniformF(const char* name, float, float, float);
		void setUniformI(const char* name, int, int, int, int);
		void setUniformF(const char* name, float, float, float, float);
		
		void setUniformVectorI(const char* name, int*, unsigned int array_count);
		void setUniformVectorF(const char* name, float*, unsigned int array_count);

		void setUniformMatrixI(const char* name, int*);
		void setUniformMatrixF(const char* name, float*);

		unsigned int GetPogramHandle();

		void Bind();
		bool IsReady();

		//Diese Funktion implementieren.
		// Diese funktion fügt die Clearable zur m_dirtyUniforms-Liste hinzu
		void notifyDirty(ICleanable* obj);

	private:
		ShaderProgramOGL3x(ShaderProgramOGL3x&){}
		ShaderProgramOGL3x& operator=( const ShaderProgramOGL3x& ) {return *this;}

		void setUniform(const char* name, void*, PrimitiveDatatype, size_t size);
		void setUniformI(const char* name, int*, size_t size);
		void setUniformUI(const char* name, unsigned int*, size_t size);
		void setUniformF(const char* name, float*, size_t size);

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