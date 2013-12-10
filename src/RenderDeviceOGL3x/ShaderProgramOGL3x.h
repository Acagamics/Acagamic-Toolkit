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
	public:
		ShaderProgramOGL3x(const std::string& vertexShaderSource, const std::string& geometryShaderSource, const std::string& fragmentShaderSource);
		~ShaderProgramOGL3x();

		unsigned int GetPogramHandle();

		void Bind();
		bool IsReady();

		void notifyDirty(ICleanable* obj);

	private:
		ShaderProgramOGL3x(ShaderProgramOGL3x&){}
		ShaderProgramOGL3x& operator=( const ShaderProgramOGL3x& ) {return *this;}

		std::string	GetProgramInfoLog();
		void findUniforms();
		
		std::hash_map<std::string,UniformOGL3x*> m_uniforms;

		unsigned int			m_program;

		ShaderObjectOGL3xPtr	m_vertexShader;
		ShaderObjectOGL3xPtr	m_geometryShader;
		ShaderObjectOGL3xPtr	m_fragmentShader;

		bool m_ready;

	};

	typedef std::shared_ptr<ShaderProgramOGL3x> ShaderProgramOGL3xPtr;
}