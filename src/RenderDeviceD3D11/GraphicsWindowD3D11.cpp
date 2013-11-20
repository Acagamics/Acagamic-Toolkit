#include "GraphicsWindowD3D11.h"

namespace ACTK
{
	bool GraphicsWindowD3D11::initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const std::string& title, WindowType windowType)
	{
		// ToDo: Erstelle das Fenster und fülle die Variablen (m_width, m_height und m_hWnd)
		return false;
	}

	void GraphicsWindowD3D11::release(void)
	{

	}

	RenderContextPtr GraphicsWindowD3D11::getContext() const
	{ 
		return m_context; 
	}

	int GraphicsWindowD3D11::getWidth() const  
	{
		return 0; 
	}
	int GraphicsWindowD3D11::getHeight() const 
	{
		return 0;
	}

	bool GraphicsWindowD3D11::shouldClose() const
	{
		return true;
	}

}