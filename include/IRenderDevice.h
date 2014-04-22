#pragma once
#include "ACTK.h"
#include "IGraphicsWindow.h"
#include "IShaderProgram.h"
#include <memory>
#include <string>

namespace ACTK
{
namespace Renderer
{
	enum class WindowType : char
	{
		Windowed,
		Fullscreen
	};

	//! RendererDevice represents the Graphics Server
	class IRenderDevice
	{
	public:
		virtual ~IRenderDevice(){}
		virtual void VRelease(void) = 0;

		// this function creates and initializes a window and a rendercontext which you can use to draw polygons
		virtual GraphicsWindowPtr	VCreateWindow(unsigned int width = 800, unsigned int height = 600, const std::string& title = "ACTK-Engine", WindowType windowType = WindowType::Windowed) = 0;
	
		virtual ShaderProgramPtr	VCreateShaderProgram(const std::string& VertexShaderSource, const std::string& FragementShaderSource) = 0;
		virtual ShaderProgramPtr	VCreateShaderProgram(const std::string& VertexShaderSource, const std::string& GeometryShaderSource, const std::string& FragementShaderSource) = 0;

		virtual Texture2DPtr		createTexture(const ) = 0;
	};

	typedef std::shared_ptr<IRenderDevice> RenderDevicePtr;
}}