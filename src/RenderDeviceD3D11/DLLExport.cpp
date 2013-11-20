#include "RenderDeviceD3D11.h"
#include "Logger.h"

namespace ACTK
{
	extern "C" __declspec(dllexport) IRenderDevice* CreateRenderDevice(HINSTANCE hInstance, EventLogger& logger)
	{
		// set the new instance of the logger to prevent the creation of a new one inside this dll
		EventLogger::SetInstance(logger);

		return new RenderDeviceD3D11(hInstance);
	}
}