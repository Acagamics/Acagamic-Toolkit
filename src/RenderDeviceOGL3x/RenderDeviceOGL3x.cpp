#include "RenderDeviceOGL3x.h"
#include "GraphicsWindowOGL3x.h"

namespace ACTK
{
	RenderDeviceOGL3x::RenderDeviceOGL3x(HINSTANCE hInstance) : m_hInstance(hInstance)
	{
		// Do nothing important here to guarantee that the instantiation succeeds without errors
	}

	RenderDeviceOGL3x::~RenderDeviceOGL3x(void)
	{

	}

	GraphicsWindowPtr RenderDeviceOGL3x::createWindow(int width, int height, const std::string& title, WindowType)
	{
		auto window = new GraphicsWindowOGL3x();

		if(window->initialize(m_hInstance, width, height, title))
			return GraphicsWindowPtr(window);
		else
			return GraphicsWindowPtr(nullptr);
	}
}