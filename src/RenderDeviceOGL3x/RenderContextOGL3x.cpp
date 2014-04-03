#include "RenderContextOGL3x.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "TypeConverterOGL3x.h"

namespace ACTK {

	RenderContextOGL3x* RenderContextOGL3x::m_currentContext;

	RenderContextOGL3x::RenderContextOGL3x(GLFWwindow* window) : m_window(window) 
	{
		if(GLEW_OK != glewInit())
		{
			LOG_ERROR("Could not initialize GLEW!");
		}
		else
		{
			LOG_INIT("GLFW sucessfully initialized.");
		}
	}

	RenderContextOGL3x::~RenderContextOGL3x(void)
	{ 
		release(); 
	}

	void RenderContextOGL3x::release(void)
	{
		m_window = nullptr;
		LOG_INIT("OpenGL RenderContext released");
	}

	void RenderContextOGL3x::clear(const ClearState& clearState)
	{
		if(m_currentContext != this)
		{
			glfwMakeContextCurrent(m_window);
			m_currentContext = this;
		}
		/*Wichtig ist dabei, dass man einen State nicht nochmal ändert, wenn der OpenGL-Wert bereits auf den Wert, den man haben möchte gestellt ist.
		*
		* Z.B.: Wenn man in einem Frame die Clearcolor auf Rosa gestellt hat, sollte man sich das merken und beim nächsten Aufruf sollte
		* die Clearcolor nicht nochmal auf rosa gestellt werden. Die OpenGL-Clearcolor sollte nur geändert werden und die OpenGL funktion nur aufgerufen werden, wenn man tatsächlich die Farbe ändert und nicht immer wieder die selbe Farbe übergibt.
		* Durch solche sinnlosen Aufrufe hat man nichts am OpenGL-State verändert, aber kostbare Zeit verschenkt.
		* 
		* Deshalb sollte man sich im RenderContextOGL3x den Clearstate, den man zuletzt gesetzt hat speichern oder ein eigenes Schatten ClearState-Objekt führen, das sich merkt,
		* welchen Zustand OpenGL gerade hat und bei jeder Änderung des OpenGL-State sollte die Schattenkopie mitgeändert werden, denn das Nachfragen über OpenGL-Funktionen welcher 
		* State gerade gesetzt ist, ist genau so teuer wie es sinnlos zu ändern.
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

	void RenderContextOGL3x::draw(PrimitiveType type ,float* vertices, unsigned int count)
	{
		for (int i = 0; i < count; i++)
		{
			glBegin(TypeConverterOGL3x::To(type));
			
			glColor3f(1.0f,0.0f,1.0f);

			glVertex3f(vertices[9*i],vertices[9*i+1],vertices[9*i+2]);
			glVertex3f(vertices[9*i+3],vertices[9*i+4],vertices[9*i+5]);
			glVertex3f(vertices[9*i+6],vertices[9*i+7],vertices[9*i+8]);

			glEnd();
		}
	}

	void RenderContextOGL3x::swapBuffers()
	{
		// Wo ist das GLFW Window?
		glfwSwapBuffers(m_window);
	}

}