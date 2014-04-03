#pragma once
#include "ACTK.h"
#include <memory>
#include "IRenderDevice.h"

namespace ACTK
{
namespace Renderer
{
	enum class API : char
	{
		OpenGL3x,
		Direct3D11
	};

	//! \brief RenderDeviceManager is a singleton and creates devices. 
	class RenderDeviceManager
	{
	protected:
		RenderDeviceManager(){}

    private:
		RenderDeviceManager( const RenderDeviceManager& ){}; //!< You shall not copy
        RenderDeviceManager& operator=( const RenderDeviceManager& ) {return *this;}

	public:
		static RenderDeviceManager& GetInstance();

		//! \brief Create an Device with an specific API
		//! \param api The API which should be used.
		//! \return shared_pointer of RenderDevice
		RenderDevicePtr CreateDevice(API api);
	};

}}