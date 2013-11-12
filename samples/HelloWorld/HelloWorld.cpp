#include "ACTK.h"
#include "AKLogger.h"
#include "RenderDeviceManager.h"

int main()
{
	FN("main(%s)", "bla");
	LOG_INIT("Dies ist ein Test: %u", 50);

	ACTK::RenderDevicePtr	Device = ACTK::RenderDeviceManager::getInstance().createDevice(ACTK::API::OpenGL3x);
	ACTK::GraphicsWindowPtr Window = Device->createWindow(800, 600, "HelloWorld");

	return 0;
}