#pragma once
#include "IRenderDevice.h"
#include <Windows.h>
#include <string>

namespace ACTK {

	class RenderDeviceOGL3x : public IRenderDevice
	{
	public:
		RenderDeviceOGL3x(HINSTANCE hInstance);
		~RenderDeviceOGL3x(void);

		// Creates Window and handles Resize and Destruction itselfs
		GraphicsWindowPtr createWindow(unsigned int width, unsigned int height, const std::string& title, WindowType windowType);

	private:
		HINSTANCE m_hInstance;
	};

}