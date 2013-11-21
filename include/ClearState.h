#pragma once
#include "ACTK.h"
#include <memory>
#include <Windows.h>

namespace ACTK
{
	struct ColorMask
	{
	public:
		bool red;
		bool green;
		bool blue;
		bool alpha;

		ColorMask(bool red, bool green, bool blue, bool alpha)
		{
			this->red = red;
			this->green = green;
			this->blue = blue;
			this->alpha = alpha;
		}

		bool operator ==(ColorMask other)
		{
			return 
				red == other.red && 
				green == other.green && 
				blue == other.blue && 
				alpha == other.alpha;
		}

		bool operator !=(ColorMask other)
		{
			return 
				red != other.red ||
				green != other.green || 
				blue != other.blue || 
				alpha != other.alpha;
		}
	};

	// this need to be a real enum (do not change into enum class)!
	typedef enum TYPE_ClearBuffers
	{
		ColorBuffer = 1,
		DepthBuffer = 2,
		StencilBuffer = 4,
		ColorAndDepthBuffer = ColorBuffer | DepthBuffer,  
		All = ColorBuffer | DepthBuffer | StencilBuffer
	} ClearBuffers;

	struct ClearState
	{
	public:
		ClearState() : ColorMask(true, true, true, true),
						DepthMask(true),
						FrontStencilMask(~0),
						BackStencilMask(~0),
						Buffers(ClearBuffers::All),
						Color(1.0f, 1.0f, 1.0f, 1.0f),
						Depth(1),
						Stencil(0)
		{
		}

		ColorMask	ColorMask;
		bool		DepthMask;
		int			FrontStencilMask;
		int			BackStencilMask;
        
		ClearBuffers Buffers;
		Color		 Color;
		float		 Depth;
		int			 Stencil;
	};

}