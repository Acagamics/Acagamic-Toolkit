#pragma once
#include "ICleanable.h"

namespace ACTK
{
	class ICleanableObserver
	{
	public:
		virtual ~ICleanableObserver(){}

		virtual void notifyDirty(ICleanable* obj) = 0;
	};
}