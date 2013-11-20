#include "AKLogger.h"
#include "GraphicsWindowOGL3x.h"

// GLFW
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"

namespace ACTK
{
	bool GraphicsWindowOGL3x::initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const std::string& title, WindowType windowType)
	{
		m_width = width;
		m_height = height;

		m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, title.c_str(), NULL, NULL), [](GLFWwindow* ptr){ glfwDestroyWindow(ptr); });
		
		if( !m_window )
		{
			glfwTerminate();
			LOG_ERROR("ERROR while creating window with glfw!");
			return false;
		}
		m_hWnd = glfwGetWin32Window(m_window.get());

		m_context = RenderContextOGL3xPtr(new RenderContextOGL3x());
		glfwMakeContextCurrent(m_window.get());
		return true;
	}

	void GraphicsWindowOGL3x::release(void)
	{
	}

	RenderContextPtr GraphicsWindowOGL3x::getContext() const
	{ 
		return m_context; 
	}

	int GraphicsWindowOGL3x::getWidth() const  
	{
		int width, height;
		glfwGetWindowSize(m_window.get(), &width, &height);
		return width; 
	}
	int GraphicsWindowOGL3x::getHeight() const 
	{
		int width, height;
		glfwGetWindowSize(m_window.get(), &width, &height);
		return height;
	}

	bool GraphicsWindowOGL3x::shouldClose() const
	{
		return glfwWindowShouldClose(m_window.get()) != 0;
	}
	
}