#pragma once
#include <memory>
#include "IRenderDevice.h"

namespace ACTK
{
	enum class API : char
	{
		OpenGL3x,
		Direct3D11
	};

	class RenderDeviceManager
	{
	protected:
		RenderDeviceManager(){}

    private:
		RenderDeviceManager( const RenderDeviceManager& ){}; // You shall not copy
        RenderDeviceManager& operator=( const RenderDeviceManager& ) {return *this;}

	public:
		static RenderDeviceManager& getInstance();
		RenderDevicePtr createDevice(API api);
	};

}