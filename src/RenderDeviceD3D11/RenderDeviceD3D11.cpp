#include "RenderDeviceD3D11.h"
#include "GraphicsWindowD3D11.h"

namespace ACTK
{
	RenderDeviceD3D11::RenderDeviceD3D11(HINSTANCE hInstance) : m_hInstance(hInstance)
	{

	}

	RenderDeviceD3D11::~RenderDeviceD3D11(void)
	{

	}

	GraphicsWindowPtr RenderDeviceD3D11::createWindow(unsigned int width, unsigned int height, const std::string& title, WindowType windowtype)
	{
		LOG_INIT("Create Direct3D Window with width: %u, height: %u.", width, height);
		auto window = std::shared_ptr<GraphicsWindowD3D11>(new GraphicsWindowD3D11());

		if(window->initialize(m_hInstance, width, height, title, windowtype))
		{
			LOG_INIT("Direct3D-Window sucessfully created.");
			return window;
		}
		else
		{
			LOG_ERROR("ERROR while creating Direct3D-Window!");
			return GraphicsWindowPtr(nullptr);
		}
	}
}