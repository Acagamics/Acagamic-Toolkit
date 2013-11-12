#include "RenderDeviceOGL3x.h"

namespace ACTK
{
	extern "C" __declspec(dllexport) IRenderDevice* CreateRenderDevice(HINSTANCE hInstance)
	{
		return new RenderDeviceOGL3x(hInstance);
	}
}