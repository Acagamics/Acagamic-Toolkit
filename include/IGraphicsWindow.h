#pragma once
#include "ACTK.h"
#include <memory>
#include <Windows.h>

#include "IRenderContext.h"

namespace ACTK
{

	class IGraphicsWindow
	{
	public:
		virtual ~IGraphicsWindow(){}
		virtual void release(void) = 0;

		virtual RenderContextPtr getContext() const = 0;
		virtual HWND getWindowHandle() const = 0;

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;
		virtual bool shouldClose() const = 0;
	};

	typedef std::shared_ptr<IGraphicsWindow> GraphicsWindowPtr;

}