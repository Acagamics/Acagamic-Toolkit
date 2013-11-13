#pragma once
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

		virtual GraphicsWindowPtr createWindow(int width = 800, int height = 600, const std::string& title = "ACTK-Engine", WindowType = WindowType::Windowed) = 0;
	};

	typedef std::shared_ptr<IRenderDevice> RenderDevicePtr;
}