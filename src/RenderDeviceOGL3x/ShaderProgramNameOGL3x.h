#pragma once
#include <string>
#include <memory>

namespace ACTK
{
	class ShaderProgramNameOGL3x
	{
	public:
		ShaderProgramNameOGL3x();
		~ShaderProgramNameOGL3x();

		unsigned int getHandle();
		std::string GetInfoLog();

	private:
		ShaderProgramNameOGL3x(ShaderProgramNameOGL3x&){}
		ShaderProgramNameOGL3x& operator=( const ShaderProgramNameOGL3x& ) {return *this;}

		unsigned int m_program;
	};
}