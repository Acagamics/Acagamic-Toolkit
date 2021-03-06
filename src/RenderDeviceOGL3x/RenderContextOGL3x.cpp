#include "RenderContextOGL3x.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "TypeConverterOGL3x.h"
#include "ShaderProgramOGL3x.h"

namespace ACTK 
{
	using namespace Core;
	using namespace Renderer;

	RenderContextOGL3x* RenderContextOGL3x::m_currentContext;

	RenderContextOGL3x::RenderContextOGL3x(GLFWwindow* window) : m_window(window) 
	{
		if(GLEW_OK != glewInit())
		{
			LOG_ERROR("Could not initialize GLEW!");
		}
		else
		{
			LOG_DEBUG("GLFW sucessfully initialized.");
		}
	}

	RenderContextOGL3x::~RenderContextOGL3x(void)
	{ 
		VRelease(); 
	}

	void RenderContextOGL3x::VRelease(void)
	{
		m_window = nullptr;
		LOG_DEBUG("OpenGL RenderContext released");
	}

	void RenderContextOGL3x::VClear(const ClearState& clearState)
	{
		if(m_currentContext != this)
		{
			glfwMakeContextCurrent(m_window);
			m_currentContext = this;
		}
		/*Wichtig ist dabei, dass man einen State nicht nochmal �ndert, wenn der OpenGL-Wert bereits auf den Wert, den man haben m�chte gestellt ist.
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
			glColorMask(clearState.ColorMask.Red, clearState.ColorMask.Green, clearState.ColorMask.Blue, clearState.ColorMask.Alpha);
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

	void RenderContextOGL3x::VDraw(PrimitiveType type ,float* vertices, ShaderProgramPtr shaderProgram, unsigned int count)
	{
		std::shared_ptr<ShaderProgramOGL3x> shaderProg = std::dynamic_pointer_cast<ShaderProgramOGL3x>(shaderProgram);

		shaderProg->Bind();

		shaderProg->CleanUniforms();

		for (int i = 0; i < count; i++)
		{
			glBegin(TypeConverterOGL3x::To(type));

			glVertex3f(vertices[9*i],vertices[9*i+1],vertices[9*i+2]);
			glVertex3f(vertices[9*i+3],vertices[9*i+4],vertices[9*i+5]);
			glVertex3f(vertices[9*i+6],vertices[9*i+7],vertices[9*i+8]);

			glEnd();
		}
	}

	void RenderContextOGL3x::VSwapBuffers()
	{
		// Wo ist das GLFW Window?
		glfwSwapBuffers(m_window);
	}

	void RenderContextOGL3x::VSetTexture2DSampler(const char* name, Texture2DPtr texture2DPtr, ShaderProgramPtr shaderProgramPtr, ImagePtr image = nullptr)
	{
		Texture2DDescription texDescription = texture2DPtr->GetDescription();
		//TODO: Load the Image.
		glTexImage2D(GL_TEXTURE_2D, 0, 
			TypeConverterOGL3x::To(texDescription.GetFormat()), 
			texDescription.GetWidth, 
			texDescription.GetHeight, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
		//TODO: Free image.
		shaderProgramPtr->VSetUniform(name, 0);
		//glUniform1i(glGetUniformLocation(shaderObjectPtr->GetShaderHandle(), "texKitten"), 0);
	}
}