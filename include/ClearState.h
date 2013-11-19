#pragma once
#include <memory>
#include <Windows.h>

namespace ACTK
{

	struct ColorMask
	{
	public:

		ColorMask(bool red, bool green, bool blue, bool alpha)
		{
			m_red = red;
			m_green = green;
			m_blue = blue;
			m_alpha = alpha;
		}

		bool GetRed()
		{
			return m_red;
		}

		bool GetGreen()
		{
			return m_green;
		}

		bool GetBlue()
		{
			return m_blue;
		}

		bool GetAlpha()
		{
			return m_alpha;
		}

		bool operator ==(ColorMask other)
		{
			return 
				m_red == other.m_red && 
				m_green == other.m_green && 
				m_blue == other.m_blue && 
				m_alpha == other.m_alpha;
		}

		bool operator !=(ColorMask other)
		{
			return 
				m_red != other.m_red ||
				m_green != other.m_green || 
				m_blue != other.m_blue || 
				m_alpha != other.m_alpha;
		}

	private:

		bool m_red;
		bool m_green;
		bool m_blue;
		bool m_alpha;
	};

	enum class ClearBuffers
	{
		ColorBuffer = 1,
		DepthBuffer = 2,
		StencilBuffer = 4,
		ColorAndDepthBuffer = ColorBuffer | DepthBuffer, 
		All = ColorBuffer | DepthBuffer | StencilBuffer
	};

	struct ClearState
	{
	public:
		ClearState() : ColorMask(true, true, true, true)
		{
			DepthMask			= true;
			FrontStencilMask	= ~0;
			BackStencilMask		= ~0;

			Buffers				= ClearBuffers::All;
			color[0]			= 1.0f;
			color[1]			= 1.0f;
			color[2]			= 1.0f;
			color[3]			= 1.0f;
			Depth				= 1;
			Stencil				= 0;
		}

		ColorMask	ColorMask;
		bool		DepthMask;
		int			FrontStencilMask;
		int			BackStencilMask;
        
		ClearBuffers Buffers;
		float		 color[4];
		float		 Depth;
		int			 Stencil;
	};

}