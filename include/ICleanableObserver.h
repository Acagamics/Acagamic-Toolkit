#include "ICleanable.h"

namespace ACTK
{
	class ICleanableObserver
	{
	public:
		virtual ~ICleanableObserver(){}

		virtual void notyfyDirty(ICleanable* obj) = 0;
	};
}