#include "ACTK.h"
#include "RenderDeviceManager.h"
#include <cstdint>


int main()
{
	uint32_t integer;

	LOG_DEBUG("Starting Game");

	// Creating Render Device
	auto DeviceOGL = ACTK::Renderer::RenderDeviceManager::GetInstance().CreateDevice(ACTK::Renderer::API::OpenGL3x);
	if(DeviceOGL == nullptr)
	{
		return 0;
	}

	// Creating Window
	auto WindowOGL = DeviceOGL->VCreateWindow(800, 600, "HelloWorld", ACTK::Renderer::WindowType::Windowed);
	if(WindowOGL == nullptr)
	{
		return 0;
	}

	// Change ClearColor
	ACTK::Renderer::ClearState cornflowerBlue;
	cornflowerBlue.Color = ACTK::Core::Color(0.392f, 0.584f, 0.929f, 1.0f);

	///////////////////////////////////////////////////////////////////
	// Gameloop
	auto ContextOGL = WindowOGL->VGetContext();

	MSG msg = { 0 };
	LOG_DEBUG("Running Game");
	while(!WindowOGL->VShouldClose())
	{
		if(PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ))
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
			// Clear Backbuffer to our ClearState
			ContextOGL->VClear(cornflowerBlue);

			ContextOGL->VSwapBuffers();
        }
	}
	LOG_DEBUG("Quitting Game");
	return (int) msg.wParam;
}