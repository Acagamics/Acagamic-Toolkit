#pragma once
#include "ACTK.h"
#include "IRenderDevice.h"
#include <Windows.h>
#include <string>
#include "ClearState.h"

struct GLFWwindow;
namespace ACTK {

	using namespace Core;
	using namespace Renderer;

	class RenderContextOGL3x : public IRenderContext
	{
		friend class GraphicsWindowOGL3x;
	public:
		RenderContextOGL3x(GLFWwindow* window);
		~RenderContextOGL3x(void);

		// =========================================================================
		// INIT/RELEASE STUFF:
		// =========================================================================
		void VRelease(void);

		// =========================================================================
		// RENDERING STUFF:
		// =========================================================================
		void VClear(const ClearState& clearState);

		void VDraw(PrimitiveType type ,float* vertices, ShaderProgramPtr shaderProgram, unsigned int count);

		void VSwapBuffers();

		void RenderContextOGL3x::VSetTexture2DSampler(const char* name, Texture2DPtr texture2DPtr, ShaderProgramPtr shaderProgramPtr, BitMapPtr image = nullptr);

	private:
		//you shall not copy
		RenderContextOGL3x(RenderContextOGL3x&){}
		RenderContextOGL3x& operator=( const RenderContextOGL3x& ) {return *this;}

		GLFWwindow* m_window;
		ClearState	m_lastClearState;

		static RenderContextOGL3x* m_currentContext;
	};

	typedef std::shared_ptr<RenderContextOGL3x> RenderContextOGL3xPtr;

}