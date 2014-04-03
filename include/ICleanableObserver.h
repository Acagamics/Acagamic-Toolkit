#pragma once
#include "ICleanable.h"

namespace ACTK
{
namespace Core
{
	class ICleanableObserver
	{
	public:
		virtual ~ICleanableObserver(){}

		virtual void NotifyDirty(ICleanable* obj) = 0;
	};
}}