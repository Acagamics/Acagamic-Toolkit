#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GraphicsWindowOGL3x.h"
#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"

namespace ACTK
{
	bool GraphicsWindowOGL3x::initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const std::string& title, WindowType windowType)
	{
		//Erstelle das Fenster und fülle die Variablen (m_width, m_height und m_hWnd)
		m_width = width;
		m_height = height;
	
		if( !glfwInit() )
			return false;
	
		GLFWwindow* window = glfwCreateWindow(width, height, "", NULL, NULL);
		
		if( !window )
		{
			glfwTerminate();
			return false;
		}
		m_hWnd = glfwGetWin32Window(window);

		return true;
	}

	void GraphicsWindowOGL3x::release(void)
	{

	}

}