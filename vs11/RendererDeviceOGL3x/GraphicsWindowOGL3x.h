#pragma once
#include "IGraphicsWindow.h"
#include <string>

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
		// Creates the Window
		bool initialize(HINSTANCE hInstance, int width, int height, std::string title);
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