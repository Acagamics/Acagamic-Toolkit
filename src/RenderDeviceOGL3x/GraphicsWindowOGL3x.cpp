#include "GraphicsWindowOGL3x.h"

// GLFW
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32

#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"

namespace ACTK
{
	using namespace Core;
	using namespace Renderer;

	GraphicsWindowOGL3x::GraphicsWindowOGL3x() :
		m_context(nullptr) 
	{

	}

	GraphicsWindowOGL3x::~GraphicsWindowOGL3x(void) 
	{ 
		VRelease(); 
	}

	void GraphicsWindowOGL3x::VRelease(void)
	{
		m_context->VRelease();

		glfwDestroyWindow(m_window);
		m_window = nullptr;

		LOG_DEBUG("OpenGL GraphicsWindow released");
	}

	bool GraphicsWindowOGL3x::Initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const std::string& title, WindowType windowType)
	{
		LOG_DEBUG("Initializing OpenGL Window");

		// Create a fullscrenn window?
		GLFWmonitor* monitor = nullptr;
		if(windowType == WindowType::Fullscreen)
			monitor = glfwGetPrimaryMonitor();

		// Creating Window with a cool custom deleter
		m_window = glfwCreateWindow(width, height, title.c_str(), monitor, NULL);
		
		if( !m_window )
		{
			glfwTerminate();
			LOG_ERROR("Error while creating window with glfw!");
			return false;
		}

		glfwMakeContextCurrent(m_window);
		m_context = RenderContextOGL3xPtr(new RenderContextOGL3x(m_window));
		return m_context != nullptr;
	}

	RenderContextPtr GraphicsWindowOGL3x::VGetContext()
	{ 
		return m_context; 
	}

	HWND GraphicsWindowOGL3x::VGetWindowHandle() const
	{
		return glfwGetWin32Window(m_window);
	}

	int GraphicsWindowOGL3x::VGetWidth() const  
	{
		int width, height;
		glfwGetWindowSize(m_window, &width, &height);
		return width; 
	}
	int GraphicsWindowOGL3x::VGetHeight() const 
	{
		int width, height;
		glfwGetWindowSize(m_window, &width, &height);
		return height;
	}

	bool GraphicsWindowOGL3x::VShouldClose() const
	{
		return glfwWindowShouldClose(m_window) != 0;
	}
	
}