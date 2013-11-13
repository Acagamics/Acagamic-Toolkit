#include <Windows.h>
#include "AKLogger.h"
#include "RenderDeviceManager.h"
#include "IRenderDevice.h"

namespace ACTK
{
	// Function inside the DLL we want to call to create our Device-Object
	extern "C"
	{
		typedef IRenderDevice* (*CREATERENDERDEVICE)(HINSTANCE hInstance);
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
					MessageBox(NULL, "Loading 'RenderDeviceOGL3x.dll' failed.", "ACTK - error", MB_OK | MB_ICONERROR);
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
					MessageBox(NULL, "Loading 'RenderDeviceD3D11.dll' failed.", "ACTK - error", MB_OK | MB_ICONERROR);
					return RenderDevicePtr(nullptr);
				}
			}
			break;
		default:
			{
				LOG_ERROR("Renderer API is not supported!");
				MessageBox(NULL, "API is not supported.", "ACTK - error", MB_OK | MB_ICONERROR);
				return RenderDevicePtr(nullptr);
			}
			break;
		}

		CREATERENDERDEVICE _CreateRenderDevice = 0;

		// Zeiger auf die dll Funktion 'CreateRenderDevice'
		_CreateRenderDevice = (CREATERENDERDEVICE) GetProcAddress(hDLL, "CreateRenderDevice");
		
		GetWindowLong(GetActiveWindow(),0);
		IRenderDevice* pDevice = _CreateRenderDevice(GetModuleHandle(NULL));

		// aufruf der dll Create-Funktionc
		if(pDevice == nullptr)
		{
			LOG_ERROR("Could not create Render Device from DLL!");
			MessageBox(NULL, "Create RenderDevice from DLL failed.", "ACTK - error", MB_OK | MB_ICONERROR);
			return RenderDevicePtr(nullptr);
		}
		else
		{
			return RenderDevicePtr(pDevice);
		}
	}
}