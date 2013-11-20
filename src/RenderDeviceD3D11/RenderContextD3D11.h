#pragma once
#include "ACTK.h"
#include "IRenderDevice.h"
#include <Windows.h>
#include <string>

struct GLFWwindow;

namespace ACTK {

	class RenderContextD3D11 : public IRenderContext
	{
	public:
		RenderContextD3D11(void);
		~RenderContextD3D11(void);

		// =========================================================================
		// INIT/RELEASE STUFF:
		// =========================================================================
		void release(void);

		// =========================================================================
		// RENDERING STUFF:
		// =========================================================================
		void clear(const ClearState& clearState);

		void swapBuffers(void);

	private:
		// you shall not copy
		RenderContextD3D11(RenderContextD3D11&){}
		RenderContextD3D11& operator=( const RenderContextD3D11& ) {return *this;}
	};

	typedef std::shared_ptr<RenderContextD3D11> RenderContextD3D11Ptr;

}