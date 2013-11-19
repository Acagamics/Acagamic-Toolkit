#include "RenderDeviceOGL3x.h"

namespace ACTK
{
	extern "C" __declspec(dllexport) IRenderDevice* CreateRenderDevice(HINSTANCE hInstance)
	{
		IRenderDevice* result = nullptr;
		result = new RenderDeviceOGL3x(hInstance);
		return result;
	}
}