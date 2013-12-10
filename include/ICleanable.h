#pragma once

namespace ACTK
{
	class ICleanable
	{
	public:
		virtual ~ICleanable(){}

		virtual void clean() = 0;
	};
}