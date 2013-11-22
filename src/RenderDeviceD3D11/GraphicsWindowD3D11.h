#pragma once
#include "ACTK.h"
#include "IRenderDevice.h"
#include "IGraphicsWindow.h"
#include "RenderContextD3D11.h"
#include <string>

struct ID3D11Device;

namespace ACTK 
{
	class GraphicsWindowD3D11 : public IGraphicsWindow
	{
	public:
		GraphicsWindowD3D11();
		~GraphicsWindowD3D11(void);

		// =========================================================================
		// INIT/RELEASE STUFF:
		// =========================================================================
		// Creates the Window and register the Windows-Callback
		bool initialize(ID3D11Device* device, HINSTANCE hInstance, unsigned int width, unsigned int height, const std::string& title, WindowType windowType);
		void release(void);

		RenderContextPtr getContext() const;

		HWND getWindowHandle() const { return m_hWnd; }
		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }
		bool shouldClose() const { return m_shouldClose; }

		void closeWindow(void) { m_shouldClose = true; }
		void updateSize(void);

	private:
		// you shall not copy
		GraphicsWindowD3D11(GraphicsWindowD3D11&){}
		GraphicsWindowD3D11& operator=( const GraphicsWindowD3D11& ) {return *this;}

		std::shared_ptr<class RenderContextD3D11> m_context;

		HWND m_hWnd;
		int m_width;
		int m_height;
		bool m_shouldClose;

		bool m_initzialized;
	};
}