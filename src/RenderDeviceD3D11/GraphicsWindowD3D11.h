#pragma once
#include "ACTK.h"
#include "IRenderDevice.h"
#include "IGraphicsWindow.h"
#include "RenderContextD3D11.h"
#include <string>

namespace ACTK 
{
	class GraphicsWindowD3D11 : public IGraphicsWindow
	{
	public:
		GraphicsWindowD3D11() : m_hWnd(0), m_width(0), m_height(0), m_shouldClose(false) {}
		~GraphicsWindowD3D11(void) {}

		// =========================================================================
		// INIT/RELEASE STUFF:
		// =========================================================================
		// Creates the Window and register the Windows-Callback
		bool initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const std::string& title, WindowType windowType);
		void release(void);

		RenderContextPtr getContext() const;
		HWND getWindowHandle() const { return m_hWnd; }

		int getWidth() const;
		int getHeight() const;
		bool shouldClose() const;

	private:
		// you shall not copy
		GraphicsWindowD3D11(GraphicsWindowD3D11&){}
		GraphicsWindowD3D11& operator=( const GraphicsWindowD3D11& ) {return *this;}

		std::shared_ptr<class RenderContextD3D11> m_context;

		HWND m_hWnd;
		int m_width;
		int m_height;
		bool m_shouldClose;
	};
}