#pragma once
#include "Logger.h"

namespace ACTK
{

	struct Color
	{
		union
		{
			float a[4];
			struct
			{
				float red, green, blue, alpha;
			};
		};

		Color(float red, float green, float blue, float alpha)
		{
			this->red = red;
			this->green = green;
			this->blue = blue;
			this->alpha = alpha;
		}

		bool operator ==(Color other)
		{
			return 
				red == other.red && 
				green == other.green && 
				blue == other.blue && 
				alpha == other.alpha;
		}

		bool operator !=(Color other)
		{
			return 
				red != other.red ||
				green != other.green || 
				blue != other.blue || 
				alpha != other.alpha;
		}
	};

}