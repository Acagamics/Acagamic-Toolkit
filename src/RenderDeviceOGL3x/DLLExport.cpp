#include "Logger.h"
#include "RenderDeviceOGL3x.h"

namespace ACTK
{
	using namespace Core;
	using namespace Renderer;

	extern "C" __declspec(dllexport) IRenderDevice* CreateRenderDevice(HINSTANCE hInstance, EventLogger& logger)
	{
		// set the new instance of the logger to prevent the creation of a new one inside this dll
		EventLogger::SetInstance(logger);

		IRenderDevice* result = nullptr;
		result = new RenderDeviceOGL3x(hInstance);
		return result;
	}
}