#pragma once
#include "IShaderProgram.h"
#include "ShaderObjectOGL3x.h"
#include "ICleanableObserver.h"
#include "UniformOGL3x.h"
#include <string>
#include <hash_map>

namespace ACTK
{
	typedef std::hash_map<std::string, UniformOGL3x*> UniformMap;

	class ShaderProgramOGL3x : public IShaderProgram, public ICleanableObserver
	{
	public:
		ShaderProgramOGL3x(const std::string& vertexShaderSource, const std::string& geometryShaderSource, const std::string& fragmentShaderSource);
		~ShaderProgramOGL3x();

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

		void notifyDirty(ICleanable* obj);

	private:
		ShaderProgramOGL3x(ShaderProgramOGL3x&){}
		ShaderProgramOGL3x& operator=( const ShaderProgramOGL3x& ) {return *this;}

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