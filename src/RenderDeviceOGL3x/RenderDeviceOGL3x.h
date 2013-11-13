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
		GraphicsWindowPtr createWindow(int width, int height, const std::string& title, WindowType);

	private:
		HINSTANCE m_hInstance;
	};

}