#include "RenderDeviceOGL3x.h"
#include "GraphicsWindowOGL3x.h"
#include "glfw3.h"

namespace ACTK
{
	RenderDeviceOGL3x::RenderDeviceOGL3x(HINSTANCE hInstance) : m_hInstance(hInstance)
	{
		if(!glfwInit() )
			LOG_ERROR("Could not initialize GLFW!");
		else
			LOG_INIT("GLFW sucessfully initialized.");
	}

	RenderDeviceOGL3x::~RenderDeviceOGL3x(void)
	{
		LOG_INIT("OpenGL Renderdevice released.");
	}

	GraphicsWindowPtr RenderDeviceOGL3x::createWindow(unsigned int width, unsigned int height, const std::string& title, WindowType windowtype)
	{
		LOG_INIT("Create OpenGL-Window with width: %u, height: %u.", width, height);
		auto window = std::shared_ptr<GraphicsWindowOGL3x>(new GraphicsWindowOGL3x());

		if(window->initialize(m_hInstance, width, height, title, windowtype))
		{
			LOG_INIT("OpenGL-Window sucessfully created.");
			return window;
		}
		else
		{
			LOG_ERROR("Error while creating OpenGL-Window!");
			return GraphicsWindowPtr(nullptr);
		}
	}
}