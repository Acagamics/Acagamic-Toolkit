#include "RenderDeviceOGL3x.h"

#include "GraphicsWindowOGL3x.h"
#include "ShaderProgramOGL3x.h"

#include "GL\glew.h"
#include "GLFW\glfw3.h"

namespace ACTK
{
	RenderDeviceOGL3x::RenderDeviceOGL3x(HINSTANCE hInstance) : m_hInstance(hInstance)
	{
		if(GL_TRUE != glfwInit())
			LOG_ERROR("Could not initialize GLFW!");
		else
		{
			LOG_DEBUG("GLFW sucessfully initialized.");
		}
	}

	void RenderDeviceOGL3x::release(void)
	{
		LOG_DEBUG("RenderDeviceOGL3x released.");
	}

	GraphicsWindowPtr RenderDeviceOGL3x::createWindow(unsigned int width, unsigned int height, const std::string& title, WindowType windowtype)
	{
		LOG_DEBUG("Create OpenGL-Window with width: %u, height: %u.", width, height);
		auto window = std::shared_ptr<GraphicsWindowOGL3x>(new GraphicsWindowOGL3x());

		if(window->initialize(m_hInstance, width, height, title, windowtype))
		{
			LOG_DEBUG("OpenGL-Window sucessfully created.");
			return window;
		}
		else
		{
			LOG_ERROR("Error while creating OpenGL-Window!");
			return GraphicsWindowPtr(nullptr);
		}
	}

	ShaderProgramPtr RenderDeviceOGL3x::createShaderProgram(const std::string& VertexShaderSource, const std::string& FragementShaderSource)
	{
		return createShaderProgram(VertexShaderSource, std::string(), FragementShaderSource);
	}

	ShaderProgramPtr RenderDeviceOGL3x::createShaderProgram(const std::string& VertexShaderSource, const std::string& GeometryShaderSource, const std::string& FragementShaderSource)
	{
		return ShaderProgramPtr(new ShaderProgramOGL3x(VertexShaderSource, GeometryShaderSource, FragementShaderSource));
	}
}