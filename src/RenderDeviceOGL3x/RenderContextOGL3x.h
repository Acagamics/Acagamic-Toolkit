#pragma once
#include "ACTK.h"
#include "IRenderDevice.h"
#include <Windows.h>
#include <string>

struct GLFWwindow;

namespace ACTK {

	class RenderContextOGL3x : public IRenderContext
	{
	public:
		RenderContextOGL3x(void){}
		~RenderContextOGL3x(void){ release(); }

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
		//you shall not copy
		RenderContextOGL3x(RenderContextOGL3x&){}
		RenderContextOGL3x& operator=( const RenderContextOGL3x& ) {return *this;}
	};

	typedef std::shared_ptr<RenderContextOGL3x> RenderContextOGL3xPtr;

}