#include "ACTK.h"
#include "RenderDeviceManager.h"
#include <cstdint>


int main()
{
	uint32_t integer;

	LOG_DEBUG("Starting Game");

	// Creating Render Device
	auto DeviceOGL = ACTK::RenderDeviceManager::getInstance().createDevice(ACTK::API::OpenGL3x);
	if(DeviceOGL == nullptr)
	{
		return 0;
	}

	// Creating Window
	auto WindowOGL = DeviceOGL->createWindow(800, 600, "HelloWorld", ACTK::WindowType::Windowed);
	if(WindowOGL == nullptr)
	{
		return 0;
	}

	// Change ClearColor
	ACTK::ClearState cornflowerBlue;
	cornflowerBlue.Color = ACTK::Color(0.392f, 0.584f, 0.929f, 1.0f);

	///////////////////////////////////////////////////////////////////
	// Gameloop
	auto ContextOGL = WindowOGL->getContext();

	MSG msg = { 0 };
	LOG_DEBUG("Running Game");
	while(!WindowOGL->shouldClose())
	{
		if(PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ))
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
			// Clear Backbuffer to our ClearState
			ContextOGL->clear(cornflowerBlue);

			ContextOGL->swapBuffers();
        }
	}
	LOG_DEBUG("Quitting Game");
	return (int) msg.wParam;
}