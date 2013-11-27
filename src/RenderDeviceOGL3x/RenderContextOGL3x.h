#pragma once
#include "ACTK.h"
#include "IRenderDevice.h"
#include <Windows.h>
#include <string>
#include "ClearState.h"

struct GLFWwindow;

namespace ACTK {

	class RenderContextOGL3x : public IRenderContext
	{
		friend class GraphicsWindowOGL3x;
	public:
		RenderContextOGL3x(GLFWwindow* window) : m_window(window) {}
		~RenderContextOGL3x(void){ release(); }

		// =========================================================================
		// INIT/RELEASE STUFF:
		// =========================================================================
		void release(void);

		// =========================================================================
		// RENDERING STUFF:
		// =========================================================================
		void clear(const ClearState& clearState);

		void swapBuffers();

	private:
		//you shall not copy
		RenderContextOGL3x(RenderContextOGL3x&){}
		RenderContextOGL3x& operator=( const RenderContextOGL3x& ) {return *this;}

		GLFWwindow* m_window;
		ClearState m_lastClearState;

		static RenderContextOGL3x* m_currentContext;
	};

	typedef std::shared_ptr<RenderContextOGL3x> RenderContextOGL3xPtr;

}