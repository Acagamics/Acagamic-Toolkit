#include "AKLogger.h"
#include "RenderDeviceOGL3x.h"
#include "GraphicsWindowOGL3x.h"
#include "GLFW\glfw3.h"

namespace ACTK
{
	RenderDeviceOGL3x::RenderDeviceOGL3x(HINSTANCE hInstance) : m_hInstance(hInstance)
	{
		// Do nothing important here to guarantee that the instantiation succeeds without errors
			if(!glfwInit() )
				LOG_ERROR("GLFW konnte nicht initialisiert werden!");
	}

	RenderDeviceOGL3x::~RenderDeviceOGL3x(void)
	{

	}

	GraphicsWindowPtr RenderDeviceOGL3x::createWindow(unsigned int width, unsigned int height, const std::string& title, WindowType windowtype)
	{
		FN("RenderDeviceOGL3x::createWindow(width = %u, height = %u, title = %s, windowtype = %u)", width, height, title, windowtype);

		LOG_INIT("Create OpenGL-Window with width: %u, height: %u.", width, height);
		auto window = new GraphicsWindowOGL3x();

		if(window->initialize(m_hInstance, width, height, title, windowtype))
		{
			LOG_INIT("OpenGL-Window sucessfully created.");
			return GraphicsWindowPtr(window);
		}
		else
		{
			LOG_ERROR("ERROR while creating OpenGL-Window!");
			return GraphicsWindowPtr(nullptr);
		}
	}
}