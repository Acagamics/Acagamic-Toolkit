#pragma once
#include "IGraphicsWindow.h"
#include <memory>
#include <string>

namespace ACTK
{
	/// @brief RendererDevice represents the Graphics Server
	class IRenderDevice
	{
	public:
		IRenderDevice(){}
		virtual ~IRenderDevice(){}

		virtual GraphicsWindowPtr createWindow(int width, int height, std::string title) =0;
	};

	typedef std::shared_ptr<IRenderDevice> RenderDevicePtr;
}