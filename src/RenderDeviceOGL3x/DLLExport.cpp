#include "RenderDeviceOGL3x.h"
#include "AKLogger.h"

namespace ACTK
{
	extern "C" __declspec(dllexport) IRenderDevice* CreateRenderDevice(HINSTANCE hInstance, EventLogger& logger)
	{
		EventLogger::SetInstance(logger);
		return new RenderDeviceOGL3x(hInstance);
	}
}