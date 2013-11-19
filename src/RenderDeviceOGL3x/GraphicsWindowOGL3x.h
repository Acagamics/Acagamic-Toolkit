#pragma once
#include "IRenderDevice.h"
#include "IGraphicsWindow.h"
#include "RenderContextOGL3x.h"
#include <string>

struct GLFWwindow;

namespace ACTK 
{
	class GraphicsWindowOGL3x : public IGraphicsWindow
	{
	public:
		GraphicsWindowOGL3x() : m_hWnd(0), m_width(0), m_height(0) {}
		~GraphicsWindowOGL3x(void) {}

		// =========================================================================
		// INIT/RELEASE STUFF:
		// =========================================================================
		// Creates the Window and register the Windows-Callback
		bool initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const std::string& title, WindowType windowType);
		void release(void);

		RenderContextPtr getContext() const;
		HWND getWindowHandle() const { return m_hWnd; }

		int getWidth() const  { return m_width; }
		int getHeight() const { return m_height; }

	private:
		std::shared_ptr<GLFWwindow> m_window;
		RenderContextOGL3xPtr m_context;

		HWND m_hWnd;
		int m_width;
		int m_height;
	};
}