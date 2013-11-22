#include "RenderDeviceD3D11.h"
#include "GraphicsWindowD3D11.h"
#include <hash_map>
#include <d3d11_1.h>

namespace ACTK
{
	// Hashmap of Windows for Callback
	std::hash_map<HWND, GraphicsWindowD3D11*> g_windows;

	RenderDeviceD3D11::RenderDeviceD3D11(HINSTANCE hInstance) : m_hInstance(hInstance), m_device(nullptr), m_releaseDevice(true), m_initzialized(false)
	{
		// create a device, device context and swap chain using the information in the scd struct
		if(SUCCEEDED(D3D11CreateDevice(NULL, 
										D3D_DRIVER_TYPE_HARDWARE,
										NULL,
										NULL,
										NULL,
										NULL,
										D3D11_SDK_VERSION,
										&m_device,
										NULL,
										NULL)))
		{
			LOG_INIT("Direct3D11 Device sucessfully created!");
			m_initzialized = true;
		}
		else
		{
			LOG_ERROR("Error while creating Direct3D11 Device!");
		}
	}

	void RenderDeviceD3D11::release(void)
	{
		if(m_initzialized)
		{
			for(auto It = g_windows.begin(); It != g_windows.end(); ++It)
			{
				It->second->release();
			}

			if(m_releaseDevice)
			{
				m_device->Release();
				m_device = nullptr;
			}
			LOG_INIT("RenderDeviceD3D11 released");
		}
		m_initzialized = false;
	}

	GraphicsWindowPtr RenderDeviceD3D11::createWindow(unsigned int width, unsigned int height, const std::string& title, WindowType windowtype)
	{
		LOG_INIT("Create Direct3D Window with width: %u, height: %u.", width, height);
		auto window = std::shared_ptr<GraphicsWindowD3D11>(new GraphicsWindowD3D11());

		if(window->initialize(m_device, m_hInstance, width, height, title, windowtype))
		{
			LOG_INIT("Direct3D-Window sucessfully created.");
			m_releaseDevice = false;
			return window;
		}
		else
		{
			LOG_ERROR("Error while creating Direct3D-Window!");
			return GraphicsWindowPtr(nullptr);
		}
	}
}