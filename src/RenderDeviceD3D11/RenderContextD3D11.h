#pragma once
#include "ACTK.h"
#include "IRenderDevice.h"
#include <Windows.h>
#include <string>

struct GLFWwindow;
struct ID3D11Device;
struct IDXGISwapChain;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

namespace ACTK {

	class RenderContextD3D11 : public IRenderContext
	{
	public:
		RenderContextD3D11(void);
		~RenderContextD3D11(void);

		// =========================================================================
		// INIT/RELEASE STUFF:
		// =========================================================================
		bool initialize(ID3D11Device* device, HWND hWnd, int width, int height, bool fullscreen);
		void release(void);

		// =========================================================================
		// RENDERING STUFF:
		// =========================================================================
		void clear(const ClearState& clearState);

		void swapBuffers(void);

	private:
		// you shall not copy
		RenderContextD3D11(RenderContextD3D11&){}
		RenderContextD3D11& operator=( const RenderContextD3D11& ) {return *this;}

		// global declarations
		IDXGISwapChain *m_swapChain;            // the pointer to the swap chain interface
		ID3D11DeviceContext *m_deviceContext;   // the pointer to our Direct3D device context
		ID3D11RenderTargetView *m_backbuffer;	// Backbuffer

		bool m_initzialized;
	};

}