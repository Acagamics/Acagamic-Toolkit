#pragma once
#include "IRenderDevice.h"
#include <Windows.h>
#include <string>

namespace ACTK {

	class RenderContextOGL3x : public IRenderContext
	{
	public:
		RenderContextOGL3x(void);
		~RenderContextOGL3x(void);

		// =========================================================================
		// INIT/RELEASE STUFF:
		// =========================================================================
		bool initialize(HWND hWnd, int width, int height);
		void release(void);

		// =========================================================================
		// RENDERING STUFF:
		// =========================================================================
		void clear(const ClearState& clearState);

		void swapBuffers(void);
	};

	typedef std::shared_ptr<RenderContextOGL3x> RenderContextOGL3xPtr;

}