#include "ACTK.h"
#include "RenderDeviceManager.h"

int main()
{
	LOG_INIT("Starting Game");
	auto DeviceOGL = ACTK::RenderDeviceManager::getInstance().createDevice(ACTK::API::Direct3D11);
	if(DeviceOGL == nullptr)
		return 0;

	auto WindowOGL = DeviceOGL->createWindow(800, 600, "HelloWorld", ACTK::WindowType::Windowed);
	if(WindowOGL == nullptr)
		return 0;

	auto ContextOGL = WindowOGL->getContext();

	ACTK::ClearState clearState;
	clearState.Color = ACTK::Color(1.0f, 0.0f, 1.0f, 1.0f); // rosa

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
			// ToDo: Implementiert die funktionen in RenderContextOGL3x
			// Ob es funktioniert hat seht ihr daran, dass das Fenster rosa wird.
			ContextOGL->clear(clearState);	// Diese Funktion wurde noch nicht implementiert.
			ContextOGL->swapBuffers();		// Diese Funktion wurde noch nicht implementiert.
        }
	}
	LOG_INIT("Quitting Game");
	return (int) msg.wParam;
}