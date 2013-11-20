#include "GraphicsWindowOGL3x.h"

// GLFW
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32
#include "glfw3.h"
#include "glfw3native.h"

namespace ACTK
{
	bool GraphicsWindowOGL3x::initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const std::string& title, WindowType windowType)
	{
		LOG_INIT("Initializing OpenGL Window");

		// Create a fullscrenn window?
		GLFWmonitor* monitor = nullptr;
		if(windowType == WindowType::Fullscreen)
			monitor = glfwGetPrimaryMonitor();

		// Creating Window with a cool custom deleter
		m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, title.c_str(), monitor, NULL), [](GLFWwindow* ptr){ glfwDestroyWindow(ptr); });
		
		
		if( !m_window )
		{
			glfwTerminate();
			LOG_ERROR("Error while creating window with glfw!");
			return false;
		}

		m_context = RenderContextOGL3xPtr(new RenderContextOGL3x());
		glfwMakeContextCurrent(m_window.get());
		
		LOG_INIT("OpenGL Window Successfully Initialized");
		return true;
	}

	void GraphicsWindowOGL3x::release(void)
	{
		LOG_INIT("OpenGL GraphicsWindow released");
	}

	RenderContextPtr GraphicsWindowOGL3x::getContext() const
	{ 
		return m_context; 
	}

	HWND GraphicsWindowOGL3x::getWindowHandle() const
	{
		return glfwGetWin32Window(m_window.get());
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