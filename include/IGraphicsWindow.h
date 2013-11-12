#pragma once
#include <memory>
#include <Windows.h>

namespace ACTK
{

	class IGraphicsWindow
	{
	public:
		virtual ~IGraphicsWindow(){}
		virtual void release(void) = 0;

		virtual HWND getWindowHandle() const = 0;

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;
	};

	typedef std::shared_ptr<IGraphicsWindow> GraphicsWindowPtr;

}