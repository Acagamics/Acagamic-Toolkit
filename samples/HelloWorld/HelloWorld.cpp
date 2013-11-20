#include "ACTK.h"
#include "AKLogger.h"
#include "RenderDeviceManager.h"

int main()
{
	auto DeviceOGL = ACTK::RenderDeviceManager::getInstance().createDevice(ACTK::API::OpenGL3x);
	auto WindowOGL = DeviceOGL->createWindow(800, 600, "HelloWorld");
	auto ContextOGL = WindowOGL->getContext();
	ACTK::ClearState clearState;
	

	///////////////////////////////////////////////////////////////////
	// Gameloop

	MSG msg = { 0 };
	LOG_INIT("Running Game");
	while(!WindowOGL->shouldClose())
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ))
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
			ContextOGL->clear(clearState);
			ContextOGL->swapBuffers();
        }
	}
	LOG_INIT("Quiting Game");
	return (int) msg.wParam;
}