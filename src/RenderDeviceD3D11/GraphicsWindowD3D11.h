#pragma once
#include "IRenderDevice.h"
#include "IGraphicsWindow.h"
#include <string>

namespace ACTK 
{
	class GraphicsWindowD3D11 : public IGraphicsWindow
	{
	public:
		GraphicsWindowD3D11() : m_hWnd(0), m_width(0), m_height(0) {}
		~GraphicsWindowD3D11(void) {}

		// =========================================================================
		// INIT/RELEASE STUFF:
		// =========================================================================

		// Creates the Window and register the Windows-Callback
		bool initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const std::string& title, WindowType windowType);
		void release(void);

		HWND getWindowHandle() const { return m_hWnd; }

		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }

	private:
		HWND m_hWnd;
		int m_width;
		int m_height;
	};
}