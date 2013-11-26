#include "RenderContextOGL3x.h"
#include "glfw3.h"

namespace ACTK {

	RenderContextOGL3x* RenderContextOGL3x::m_currentContext;

	void RenderContextOGL3x::release(void)
	{
		LOG_INIT("OpenGL RenderContext released");
	}

	void RenderContextOGL3x::clear(const ClearState& clearState)
	{
		if(m_currentContext != this)
		{
			glfwMakeContextCurrent(m_window);
			m_currentContext = this;
		}
		/* ToDo: Das �bergebene ClearState objekt enh�lt die Parameter auf die die der Context eingestellt werden muss.
		* Wichtig ist dabei, dass man einen State nicht nochmal �ndert, wenn der OpenGL-Wert bereits auf den Wert, den man haben m�chte gestellt ist.
		*
		* Z.B.: Wenn man in einem Frame die Clearcolor auf Rosa gestellt hat, sollte man sich das merken und beim n�chsten Aufruf sollte
		* die Clearcolor nicht nochmal auf rosa gestellt werden. Die OpenGL-Clearcolor sollte nur ge�ndert werden und die OpenGL funktion nur aufgerufen werden, wenn man tats�chlich die Farbe �ndert und nicht immer wieder die selbe Farbe �bergibt.
		* Durch solche sinnlosen Aufrufe hat man nichts am OpenGL-State ver�ndert, aber kostbare Zeit verschenkt.
		* 
		* Deshalb sollte man sich im RenderContextOGL3x den Clearstate, den man zuletzt gesetzt hat speichern oder ein eigenes Schatten ClearState-Objekt f�hren, das sich merkt,
		* welchen Zustand OpenGL gerade hat und bei jeder �nderung des OpenGL-State sollte die Schattenkopie mitge�ndert werden, denn das Nachfragen �ber OpenGL-Funktionen welcher 
		* State gerade gesetzt ist, ist genau so teuer wie es sinnlos zu �ndern.
		*/

		if(m_lastClearState.ColorMask != clearState.ColorMask)
		{
			m_lastClearState.ColorMask = clearState.ColorMask;
			glColorMask(clearState.ColorMask.red, clearState.ColorMask.green, clearState.ColorMask.blue, clearState.ColorMask.alpha);
		}
		if(m_lastClearState.DepthMask != clearState.DepthMask)
		{
			m_lastClearState.DepthMask = clearState.DepthMask;
			glDepthMask(clearState.DepthMask);
		}
		if(m_lastClearState.Color != clearState.Color)
		{
			m_lastClearState.Color = clearState.Color;
			glClearColor(clearState.Color.red, clearState.Color.green, clearState.Color.blue, clearState.Color.alpha); 
		}
		if(m_lastClearState.Depth != clearState.Depth)
		{
			m_lastClearState.Depth = clearState.Depth;
			glClearDepth(clearState.Depth);
		}
		if(m_lastClearState.Stencil != clearState.Stencil)
		{
			m_lastClearState.Stencil = clearState.Stencil;
			glClearStencil(clearState.Stencil); 
		}

		// specifies which buffer needs to be cleared

		GLbitfield clearMask = 0;
		if ((clearState.Buffers & ClearBuffers::ColorBuffer) != 0)
		{
			clearMask |= GL_COLOR_BUFFER_BIT;
		}

		if ((clearState.Buffers & ClearBuffers::DepthBuffer) != 0)
		{
			clearMask |= GL_DEPTH_BUFFER_BIT;
		}

		if ((clearState.Buffers & ClearBuffers::StencilBuffer) != 0)
		{
			clearMask |= GL_STENCIL_BUFFER_BIT;
		}
		glClear(clearMask);
	}

	void RenderContextOGL3x::swapBuffers()
	{
		// Wo ist das GLFW Window?
		glfwSwapBuffers(m_window);
	}

}