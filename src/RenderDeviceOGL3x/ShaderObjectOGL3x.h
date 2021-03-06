#pragma once
#include <memory>

namespace ACTK
{
	using namespace Core;

	class ShaderObjectOGL3x
	{
	public:
		ShaderObjectOGL3x(unsigned int shaderType, const std::string& source);
		~ShaderObjectOGL3x();

		unsigned int	GetShaderHandle();
		bool			IsReady();

	private:
		ShaderObjectOGL3x(ShaderObjectOGL3x&){}
		ShaderObjectOGL3x& operator=( const ShaderObjectOGL3x& ) {return *this;}

		std::string		GetCompileLog();

		unsigned int	m_shaderObject;
		int				m_result;
	};

	typedef std::shared_ptr<ShaderObjectOGL3x> ShaderObjectOGL3xPtr;
}