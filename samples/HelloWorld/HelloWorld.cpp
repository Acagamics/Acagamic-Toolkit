#include "ACTK.h"
#include "AKLogger.h"
#include "RenderDeviceManager.h"

int main()
{
	ACTK::RenderDevicePtr	DeviceOGL = ACTK::RenderDeviceManager::getInstance().createDevice(ACTK::API::OpenGL3x);
	ACTK::GraphicsWindowPtr WindowOGL = DeviceOGL->createWindow(800, 600, "HelloWorld");

	ACTK::RenderDevicePtr	DeviceD3D = ACTK::RenderDeviceManager::getInstance().createDevice(ACTK::API::Direct3D11);
	ACTK::GraphicsWindowPtr WindowD3D = DeviceD3D->createWindow(800, 600, "HelloWorld");

	return 0;
}