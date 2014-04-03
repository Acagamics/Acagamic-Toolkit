#pragma once

namespace ACTK
{
namespace Core
{
	class ICleanable
	{
	public:
		virtual ~ICleanable(){}

		virtual void Clean() = 0;
	};
}}