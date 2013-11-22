#pragma once
#include "ACTK.h"
#include "IRenderDevice.h"
#include <Windows.h>
#include <string>

struct ID3D11Device;

namespace ACTK {

	class RenderDeviceD3D11 : public IRenderDevice
	{
	public:
		RenderDeviceD3D11(HINSTANCE hInstance);
		~RenderDeviceD3D11(void){ release(); }
		void release(void);

		// Creates Window and handles Resize and Destruction itselfs
		GraphicsWindowPtr createWindow(unsigned int width, unsigned int height, const std::string& title, WindowType windowType);
	
	private:
		// you shall not copy
		RenderDeviceD3D11(RenderDeviceD3D11&){}
		RenderDeviceD3D11& operator=( const RenderDeviceD3D11& ) {return *this;}

		HINSTANCE m_hInstance;
		ID3D11Device *m_device; // the pointer to our Direct3D device interface
		bool m_releaseDevice;

		bool m_initzialized;
	};

}