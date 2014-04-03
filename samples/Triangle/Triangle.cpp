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

	// TODO: Buffer erstellen und mit Dreieckinformationen f�llen

		// Dreieck-Koordinaten, die ohne Kamera in dem Fenster zu sehen sein m�ssten
		float* vertices = new float[9];     // vertex array 
		vertices[0] =-0.3f; vertices[1] = 0.5f; vertices[2] =-1.0f;
		vertices[3] =-0.8f; vertices[4] =-0.5f; vertices[5] =-1.0f;
		vertices[6] = 0.2f; vertices[7] =-0.5f; vertices[8]= -1.0f;

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

			// TODO: Dreieck zeichnen mit dem Context
				
				// So ungef�hr muss der Aufruf aussehen. �ndere daf�r das Interface entsprechend und implementiere die Funktion in der DLL
				//ContextOGL->draw( PrimitiveType, Offset, Count, VertexArray, ShaderProgram, RenderState );
				
				// PrimitiveType	= Was soll gezeichnet werden? Dreieck, Linie, Punkte
				// Offset			= Ab welchem Index Dreieck in dem VertexArray
				// Count			= Wie viele Koordinaten nach dem Offset die gezeichnet werden m�ssen
				// VertexArray		= Dreieckskoordinaten
				// Shader Program	= Das ShaderProgramm (Vertex und Pixelshader) mit dem die Dreiecke gezeichnet werden sollen
				// RenderState		= Die RenderState einstellungen die f�r das Zeichnen dieses Dreiecks vorgenommen werden sollen

			ContextOGL->swapBuffers();
        }
	}
	LOG_INIT("Quitting Game");
	return (int) msg.wParam;
}