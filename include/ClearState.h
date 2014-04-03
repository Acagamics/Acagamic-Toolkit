#pragma once
#include "ACTK.h"
#include <memory>
#include <Windows.h>

namespace ACTK
{
namespace Renderer
{
	using namespace Core;

	struct ColorMask
	{
	public:
		bool Red;
		bool Green;
		bool Blue;
		bool Alpha;

		ColorMask(bool red, bool green, bool blue, bool alpha)
		{
			this->Red = red;
			this->Green = green;
			this->Blue = blue;
			this->Alpha = alpha;
		}

		bool operator ==(ColorMask other)
		{
			return 
				Red == other.Red && 
				Green == other.Green && 
				Blue == other.Blue && 
				Alpha == other.Alpha;
		}

		bool operator !=(ColorMask other)
		{
			return 
				Red != other.Red ||
				Green != other.Green || 
				Blue != other.Blue || 
				Alpha != other.Alpha;
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
						Buffers(ClearBuffers::All),
						Color(1.0f, 1.0f, 1.0f, 1.0f),
						Depth(1),
						Stencil(0)
		{
		}

		ColorMask	ColorMask;
		bool		DepthMask;
        
		ClearBuffers Buffers;
		Color		 Color;
		float		 Depth;
		int			 Stencil;

		bool operator ==(const ClearState& right)
		{
			return 
				ColorMask == right.ColorMask && 
				DepthMask == right.DepthMask && 
				Buffers == right.Buffers &&
				Color == right.Color && 
				Depth == right.Depth &&
				Stencil == right.Stencil;
		}

		bool operator !=(const ClearState& right)
		{
			return 
				ColorMask != right.ColorMask || 
				DepthMask != right.DepthMask || 
				Buffers != right.Buffers ||
				Color != right.Color || 
				Depth != right.Depth ||
				Stencil != right.Stencil;
		}
	};
}}