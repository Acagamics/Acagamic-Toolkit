#include "RenderDeviceOGL3x.h"
#include "AKLogger.h"

namespace ACTK
{
	extern "C" __declspec(dllexport) IRenderDevice* CreateRenderDevice(HINSTANCE hInstance, EventLogger& logger)
	{
		EventLogger::SetInstance(logger);
		IRenderDevice* result = nullptr;
		result = new RenderDeviceOGL3x(hInstance);
		return result;
	}
}