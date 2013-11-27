#pragma once
#include <memory>

namespace ACTK
{
	class IShaderProgram
	{
	public:
		virtual ~IShaderProgram(){}
	};

	typedef std::shared_ptr<IShaderProgram> ShaderProgramPtr;
}