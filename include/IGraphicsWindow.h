#pragma once
#include "ACTK.h"
#include <memory>
#include <Windows.h>

#include "IRenderContext.h"

namespace ACTK
{
namespace Renderer
{
	class IGraphicsWindow
	{
	public:
		virtual ~IGraphicsWindow(){}
		virtual void VRelease(void) = 0;

		virtual RenderContextPtr VGetContext() = 0;
		virtual HWND VGetWindowHandle() const = 0;

		virtual int VGetWidth() const = 0;
		virtual int VGetHeight() const = 0;
		virtual bool VShouldClose() const = 0;
	};

	typedef std::shared_ptr<IGraphicsWindow> GraphicsWindowPtr;

}}