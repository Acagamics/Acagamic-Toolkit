#pragma once
#include "IShaderProgram.h"

#include "ShaderProgramNameOGL3x.h"
#include "ShaderObjectOGL3x.h"

#include <string>

namespace ACTK
{
	class ShaderProgramOGL3x : public IShaderProgram
	{
	public:
		ShaderProgramOGL3x(const std::string& vertexShaderSource, const std::string& geometryShaderSource, const std::string& fragmentShaderSource);
		~ShaderProgramOGL3x();

		unsigned int GetPogramHandle();

		void Bind();
		bool IsReady();

	private:
		ShaderProgramOGL3x(ShaderProgramOGL3x&){}
		ShaderProgramOGL3x& operator=( const ShaderProgramOGL3x& ) {return *this;}

		std::string	GetProgramInfoLog();

		ShaderProgramNameOGL3x*	m_program;

		ShaderObjectOGL3x*		m_vertexShader;
		ShaderObjectOGL3x*		m_geometryShader;
		ShaderObjectOGL3x*		m_fragmentShader;

		bool m_ready;
	};
}