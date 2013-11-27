#pragma once
#include <string>
#include <memory>

namespace ACTK
{
	class ShaderObjectNameOGL3x
	{
	public:
		ShaderObjectNameOGL3x(unsigned int ShaderType);
		~ShaderObjectNameOGL3x();

		unsigned int getValue();

		std::string GetInfoLog();

	private:
		ShaderObjectNameOGL3x(ShaderObjectNameOGL3x&){}
		ShaderObjectNameOGL3x& operator=( const ShaderObjectNameOGL3x& ) {return *this;}

		unsigned int m_shader;
	};

	typedef std::shared_ptr<ShaderObjectNameOGL3x> ShaderObjectNameOGL3xPtr;
}