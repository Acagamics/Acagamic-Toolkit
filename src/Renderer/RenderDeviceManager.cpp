#include <Windows.h>
#include "RenderDeviceManager.h"
#include "IRenderDevice.h"

namespace ACTK
{
	// Function inside the DLL we want to call to create our Device-Object
	extern "C"
	{
		typedef IRenderDevice* (*CREATERENDERDEVICE)(HINSTANCE hInstance, EventLogger& logger);
	}

	RenderDeviceManager& RenderDeviceManager::getInstance()
	{
		static RenderDeviceManager instance;
		return instance;
	}

	RenderDevicePtr RenderDeviceManager::createDevice(API api)
	{
		HMODULE hDLL = NULL;
		switch(api)
		{
		case API::OpenGL3x:
			{
				#ifdef _DEBUG
					hDLL = LoadLibraryExW(L"RenderDeviceOGL3x_d.dll", NULL, 0);
				#else
					hDLL = LoadLibraryExW(L"RenderDeviceOGL3x.dll", NULL, 0);
				#endif
				if(!hDLL)
				{
					LOG_ERROR("Could not find RenderDeviceOGL3x.dll!");
					return RenderDevicePtr(nullptr);
				}
			}
			break;
		case API::Direct3D11:
			{
				#ifdef _DEBUG
					hDLL = LoadLibraryExW(L"RenderDeviceD3D11_d.dll", NULL, 0);
				#else
					hDLL = LoadLibraryExW(L"RenderDeviceD3D11.dll", NULL, 0);
				#endif
				if(!hDLL)
				{
					LOG_ERROR("Could not find RenderDeviceD3D11.dll!");
					return RenderDevicePtr(nullptr);
				}
			}
			break;
		default:
			{
				LOG_ERROR("Renderer API is not supported!");
				return RenderDevicePtr(nullptr);
			}
			break;
		}

		CREATERENDERDEVICE _CreateRenderDevice = 0;

		// Zeiger auf die dll Funktion 'CreateRenderDevice'
		_CreateRenderDevice = (CREATERENDERDEVICE) GetProcAddress(hDLL, "CreateRenderDevice");
		
		GetWindowLong(GetActiveWindow(),0);
		IRenderDevice* pDevice = _CreateRenderDevice(GetModuleHandle(NULL), ACTK::EventLogger::GetInstance());

		// aufruf der dll Create-Funktionc
		if(pDevice == nullptr)
		{
			LOG_ERROR("Could not create Render Device from DLL!");
		}
		return RenderDevicePtr(pDevice);
	}
}