#pragma once
#include "IShaderProgram.h"
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

		unsigned int			m_program;

		ShaderObjectOGL3xPtr	m_vertexShader;
		ShaderObjectOGL3xPtr	m_geometryShader;
		ShaderObjectOGL3xPtr	m_fragmentShader;

		bool m_ready;
	};

	typedef std::shared_ptr<ShaderProgramOGL3x> ShaderProgramOGL3xPtr;
}