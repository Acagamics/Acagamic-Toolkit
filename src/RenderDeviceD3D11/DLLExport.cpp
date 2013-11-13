#include "RenderDeviceD3D11.h"

namespace ACTK
{
	extern "C" __declspec(dllexport) IRenderDevice* CreateRenderDevice(HINSTANCE hInstance)
	{
		return new RenderDeviceD3D11(hInstance);
	}
}