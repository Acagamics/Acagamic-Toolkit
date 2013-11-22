#include "RenderContextD3D11.h"
#include <d3d11_1.h>

namespace ACTK {

	RenderContextD3D11::RenderContextD3D11(void) : m_swapChain(nullptr), m_deviceContext(nullptr), m_backbuffer(nullptr), m_initzialized(false)
	{

	}

	RenderContextD3D11::~RenderContextD3D11(void)
	{
		release();
		
	}

	void RenderContextD3D11::release(void)
	{
		if(m_initzialized)
		{
			if(m_swapChain != nullptr)
			{
				m_swapChain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode
				m_swapChain->Release();
				m_swapChain = nullptr;
			}

			if(m_backbuffer != nullptr)
			{
				m_backbuffer->Release();
				m_backbuffer = nullptr;
			}

			if(m_deviceContext != nullptr)
			{
				m_deviceContext->Release();
				m_deviceContext = nullptr;
			}
			LOG_INIT("RenderContextD3D11 released");
		}
		m_initzialized = false;
	}

	bool RenderContextD3D11::initialize(ID3D11Device* device, HWND hWnd, int width, int height, bool fullscreen)
	{
		// create a struct to hold information about the swap chain
		DXGI_SWAP_CHAIN_DESC swapChainDescription;

		// clear out the struct for use
		ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

		// fill the swap chain description struct
		swapChainDescription.BufferCount = 1;                                   // one back buffer
		swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // use 32-bit color
		
		swapChainDescription.BufferDesc.Width = width;							// set the back buffer width
		swapChainDescription.BufferDesc.Height = height;						// set the back buffer height
		swapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // allow full-screen switching

		swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // how swap chain is to be used
		swapChainDescription.OutputWindow = hWnd;                               // the window to be used
		swapChainDescription.SampleDesc.Count = 4;                              // how many multisamples
		swapChainDescription.Windowed = !fullscreen;                            // windowed/full-screen mode

		if(SUCCEEDED(D3D11CreateDeviceAndSwapChain(	NULL, 
													D3D_DRIVER_TYPE_HARDWARE,
													NULL,
													NULL,
													NULL,
													NULL,
													D3D11_SDK_VERSION,
													&swapChainDescription,
													&m_swapChain,
													NULL,
													NULL,
													&m_deviceContext)))
		{
			LOG_INIT("Direct3D11 Context sucessfully created!");
		}
		else
		{
			LOG_ERROR("Error while creating Direct3D11 Context!");
		}

		// get the address of the back buffer
		ID3D11Texture2D *pBackBuffer = nullptr;
		m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		// use the back buffer address to create the render target
		bool result = SUCCEEDED(device->CreateRenderTargetView(pBackBuffer, NULL, &m_backbuffer));
		pBackBuffer->Release();
		pBackBuffer = nullptr;

		if(!result)
		{
			LOG_ERROR("Error while creating DirectX11 RenderTargetView.");
			return false;
		}

		// set the render target as the back buffer
		m_deviceContext->OMSetRenderTargets(1, &m_backbuffer, NULL);

		m_initzialized = true;
		return true;
	}

	void RenderContextD3D11::clear(const ClearState& clearState)
	{
		// clear the back buffer to a deep blue
		m_deviceContext->ClearRenderTargetView(m_backbuffer, clearState.Color.a);
	}

	void RenderContextD3D11::swapBuffers(void)
	{
		// switch the back buffer and the front buffer
		m_swapChain->Present(0, 0);
	}

}