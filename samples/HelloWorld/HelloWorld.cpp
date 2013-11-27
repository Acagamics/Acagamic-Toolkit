#include "ACTK.h"
#include "RenderDeviceManager.h"
#include <cstdint>

#include "resource.h"

std::string LoadShader(int name)
{
	DWORD size = 0;
    const char* data = NULL;
    HMODULE handle = ::GetModuleHandle(NULL);
    HRSRC rc = ::FindResource(handle, MAKEINTRESOURCE(name), MAKEINTRESOURCE(SHADER));
    HGLOBAL rcData = ::LoadResource(handle, rc);
    size = ::SizeofResource(handle, rc);
	return std::string(static_cast<const char*>(::LockResource(rcData)));
}

int main()
{
	uint32_t integer;

	LOG_INIT("Starting Game");
	auto DeviceOGL = ACTK::RenderDeviceManager::getInstance().createDevice(ACTK::API::OpenGL3x);
	if(DeviceOGL == nullptr)
	{
		return 0;
	}
	auto WindowOGL = DeviceOGL->createWindow(800, 600, "HelloWorld", ACTK::WindowType::Windowed);
	if(WindowOGL == nullptr)
	{
		return 0;
	}
	auto ShaderProgram = DeviceOGL->createShaderProgram(LoadShader(IDS_VERTEXSHADER), LoadShader(IDS_FRAGMENTSHADER));

	ACTK::ClearState cornflowerBlue;
	cornflowerBlue.Color = ACTK::Color(0.392f, 0.584f, 0.929f, 1.0f);

	///////////////////////////////////////////////////////////////////
	// Gameloop
	auto ContextOGL = WindowOGL->getContext();

	MSG msg = { 0 };
	LOG_INIT("Running Game");
	while(!WindowOGL->shouldClose())
	{
		if(PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ))
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
			ContextOGL->clear(cornflowerBlue);
			ContextOGL->swapBuffers();
        }
	}
	LOG_INIT("Quitting Game");
	return (int) msg.wParam;
}