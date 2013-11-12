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

		GraphicsWindowPtr createWindow(int width, int height, std::string title);
	private:
		HINSTANCE m_hInstance;
	};

}