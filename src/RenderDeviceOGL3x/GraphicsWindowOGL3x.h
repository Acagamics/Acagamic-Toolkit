#pragma once
#include "ACTK.h"
#include "IRenderDevice.h"
#include "IGraphicsWindow.h"
#include "RenderContextOGL3x.h"
#include <string>

struct GLFWwindow;

namespace ACTK 
{
	using namespace Core;
	using namespace Renderer;

	class GraphicsWindowOGL3x : public IGraphicsWindow
	{
	public:
		GraphicsWindowOGL3x();
		~GraphicsWindowOGL3x(void);

		// =========================================================================
		// INIT/RELEASE STUFF:
		// =========================================================================
		// Creates the Window and register the Windows-Callback
		bool Initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const std::string& title, WindowType windowType);
		void VRelease(void);

		RenderContextPtr VGetContext();
		HWND VGetWindowHandle() const;

		int VGetWidth() const;
		int VGetHeight() const;
		bool VShouldClose() const;

	private:
		//you shall not copy
		GraphicsWindowOGL3x(GraphicsWindowOGL3x&) : m_context(nullptr){}
		GraphicsWindowOGL3x& operator=( const GraphicsWindowOGL3x& ) {return *this;}

		GLFWwindow			   *m_window;
		RenderContextOGL3xPtr	m_context;
	};

	typedef std::shared_ptr<GraphicsWindowOGL3x> GraphicsWindowOGL3xPtr;
}