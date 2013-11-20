#pragma once
#include "ACTK.h"
#include "IGraphicsWindow.h"
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
		IRenderDevice(){}
		virtual ~IRenderDevice(){}

		// this function creates and initializes a window and a rendercontext which you can use to draw polygons
		virtual GraphicsWindowPtr createWindow(unsigned int width = 800, unsigned int height = 600, const std::string& title = "ACTK-Engine", WindowType windowType = WindowType::Windowed) = 0;
	};

	typedef std::shared_ptr<IRenderDevice> RenderDevicePtr;
}