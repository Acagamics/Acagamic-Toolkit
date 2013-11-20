#pragma once
#include "ACTK.h"
#include "IRenderDevice.h"
#include <Windows.h>
#include <string>

namespace ACTK {

	class RenderDeviceD3D11 : public IRenderDevice
	{
	public:
		RenderDeviceD3D11(HINSTANCE hInstance);
		~RenderDeviceD3D11(void);

		// Creates Window and handles Resize and Destruction itselfs
		GraphicsWindowPtr createWindow(unsigned int width, unsigned int height, const std::string& title, WindowType windowType);

	private:
		// you shall not copy
		RenderDeviceD3D11(RenderDeviceD3D11&){}
		RenderDeviceD3D11& operator=( const RenderDeviceD3D11& ) {return *this;}

		HINSTANCE m_hInstance;
	};

}