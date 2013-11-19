#pragma once
#include <memory>
#include <Windows.h>
#include "ClearState.h"

namespace ACTK
{

	class IRenderContext
	{
	public:
		virtual ~IRenderContext(){}

		// =========================================================================
		// INIT/RELEASE STUFF:
		// =========================================================================
		virtual void release(void) = 0;

		// =========================================================================
		// RENDERING STUFF:
		// =========================================================================
		virtual void clear(const ClearState& clearState) = 0;

		virtual void swapBuffers(void) = 0;
	};

	typedef std::shared_ptr<IRenderContext> RenderContextPtr;

}