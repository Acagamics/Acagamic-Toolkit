#include "ACTK.h"
#include "RenderDeviceManager.h"

int main()
{
	LOG_INIT("Starting Game");
	auto DeviceOGL = ACTK::RenderDeviceManager::getInstance().createDevice(ACTK::API::OpenGL3x);
	if(DeviceOGL == nullptr)
		return 0;

	auto WindowOGL = DeviceOGL->createWindow(800, 600, "HelloWorld", ACTK::WindowType::Windowed);
	auto WindowOGL2 = DeviceOGL->createWindow(800, 600, "HelloWorld", ACTK::WindowType::Windowed);
	if(WindowOGL == nullptr)
		return 0;

	auto ContextOGL = WindowOGL->getContext();
	auto ContextOGL2 = WindowOGL2->getContext();
	if(ContextOGL == nullptr)
		return 0;

	ACTK::ClearState clearState;
	clearState.Color = ACTK::Color(1.0f, 0.0f, 1.0f, 1.0f); // rosa

	ACTK::ClearState cornflowerBlue;
	cornflowerBlue.Color = ACTK::Color(0.392f, 0.584f, 0.929f, 1.0f);

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

			ContextOGL2->clear(cornflowerBlue);
			ContextOGL2->swapBuffers();
        }
	}
	LOG_INIT("Quitting Game");
	return (int) msg.wParam;
}