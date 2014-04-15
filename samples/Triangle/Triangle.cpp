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
	LOG_DEBUG("Starting Game");
	auto DeviceOGL = ACTK::Renderer::RenderDeviceManager::GetInstance().CreateDevice(ACTK::Renderer::API::OpenGL3x);
	if(DeviceOGL == nullptr)
	{
		return 0;
	}
	auto WindowOGL = DeviceOGL->VCreateWindow(800, 600, "HelloWorld", ACTK::Renderer::WindowType::Windowed);
	if(WindowOGL == nullptr)
	{
		return 0;
	}
	auto ShaderProgram = DeviceOGL->VCreateShaderProgram(LoadShader(IDS_VERTEXSHADER), LoadShader(IDS_FRAGMENTSHADER));

	///////////////////////////////////////////////////////////////////
	// ClearState and Color

	ACTK::Renderer::ClearState cornflowerBlue;
	cornflowerBlue.Color = ACTK::Renderer::Color(0.392f, 0.584f, 0.929f, 1.0f);

	///////////////////////////////////////////////////////////////////
	// Vertex Array
	
	// Dreieck-Koordinaten, die ohne Kamera in dem Fenster zu sehen sein müssten
	float* vertices = new float[9];     // vertex array 
	vertices[0] =-0.3f; vertices[1] = 0.5f; vertices[2] =-1.0f;
	vertices[3] =-0.8f; vertices[4] =-0.5f; vertices[5] =-1.0f;
	vertices[6] = 0.2f; vertices[7] =-0.5f; vertices[8]= -1.0f;

	// TODO: Buffer erstellen und mit Dreieckinformationen füllen
	

	///////////////////////////////////////////////////////////////////
	// Uniforms
	float white[] = {1.0f, 1.0f, 1.0f};
	ShaderProgram->VSetUniformVector("u_color", white, 3);

	///////////////////////////////////////////////////////////////////
	// RenderState
		
	// TODO: RenderState

		// So ungefähr soll es aussehen
		// ACTK::RenderState renderState;
		// renderState.FacetCulling.Enabled = false;
		// renderState.DepthTest.Enabled = false;

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
			ContextOGL->VClear(cornflowerBlue);
			
			// TODO: Dreieck zeichnen mit dem Context
				
				// So ungefähr muss der Aufruf aussehen. Ändere dafür das Interface entsprechend und implementiere die Funktion in der DLL
				//ContextOGL->draw( PrimitiveType, Offset, Count, VertexArray, ShaderProgram, RenderState );
				
				// PrimitiveType	= Was soll gezeichnet werden? Dreieck, Linie, Punkte
				// Offset			= Ab welchem Index Dreieck in dem VertexArray
				// Count			= Wie viele Koordinaten nach dem Offset die gezeichnet werden müssen
				// VertexArray		= Dreieckskoordinaten
				// Shader Program	= Das ShaderProgramm (Vertex und Pixelshader) mit dem die Dreiecke gezeichnet werden sollen
				// RenderState		= Die RenderState Einstellungen die für das Zeichnen dieses Dreiecks vorgenommen werden sollen

				// Das machen wir schrittweise: (Dreiecke mit GlBegin() und GLEnd() zeichnen;
				// 1. Schritt: ContextOGL->draw( VertexArray, ShaderProgram );												// alle dreiecke zeichnen
				// 2. Schritt: ContextOGL->draw( Offset, Count, VertexArray, ShaderProgram );								// nickt alle dreiecke zeichnen
				// 3. Schritt: ContextOGL->draw( PrimitiveType, Offset, Count, VertexArray, ShaderProgram );				// Dreieck als Linie oder Punkte zeichnen
				// 5. Schritt: ContextOGL->draw( PrimitiveType, Offset, Count, VertexArray, ShaderProgram, RenderState );	// RenderState einstellen

				// 6. Schritt: Das selbe mit Vertex Buffern
			ContextOGL->VDraw(ACTK::Renderer::PrimitiveType::LineLoop, vertices, ShaderProgram, 1);
			ContextOGL->VSwapBuffers();
        }
	}
	LOG_DEBUG("Quitting Game");
	return (int) msg.wParam;
}