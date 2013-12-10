#pragma once
#include <memory>

namespace ACTK
{
	class IShaderProgram
	{
	public:
		virtual ~IShaderProgram(){}

		virtual void setUniformI(const char* name, int) = 0;
		virtual void setUniformF(const char* name, float) = 0;
		virtual void setUniformI(const char* name, int, int) = 0;
		virtual void setUniformF(const char* name, float, float) = 0;
		virtual void setUniformI(const char* name, int, int, int) = 0;
		virtual void setUniformF(const char* name, float, float, float) = 0;
		virtual void setUniformI(const char* name, int, int, int, int) = 0;
		virtual void setUniformF(const char* name, float, float, float, float) = 0;
		
		virtual void setUniformVectorI(const char* name, int*, unsigned int array_count = 0) = 0;
		virtual void setUniformVectorF(const char* name, float*, unsigned int array_count = 0) = 0;

		virtual void setUniformMatrixI(const char* name, int*) = 0;
		virtual void setUniformMatrixF(const char* name, float*) = 0;
	};

	typedef std::shared_ptr<IShaderProgram> ShaderProgramPtr;
}