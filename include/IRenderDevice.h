#pragma once
#include "ACTK.h"
#include "IGraphicsWindow.h"
#include "IShaderProgram.h"
#include <memory>
#include <string>

namespace ACTK
{
	enum class WindowType : char
	{
		Windowed,
		Fullscreen
	};

	/// @brief RendererDevice represents the Graphics Server
	class IRenderDevice
	{
	public:
		virtual ~IRenderDevice(){}
		virtual void release(void) = 0;

		// this function creates and initializes a window and a rendercontext which you can use to draw polygons
		virtual GraphicsWindowPtr	createWindow(unsigned int width = 800, unsigned int height = 600, const std::string& title = "ACTK-Engine", WindowType windowType = WindowType::Windowed) = 0;
	
		virtual ShaderProgramPtr	createShaderProgram(const std::string& VertexShaderSource, const std::string& FragementShaderSource) = 0;
		virtual ShaderProgramPtr	createShaderProgram(const std::string& VertexShaderSource, const std::string& GeometryShaderSource, const std::string& FragementShaderSource) = 0;
	};

	typedef std::shared_ptr<IRenderDevice> RenderDevicePtr;
}