#include "GraphicsWindowD3D11.h"
#include <hash_map>

namespace ACTK
{
	extern std::hash_map<HWND, GraphicsWindowD3D11*> g_windows;
	//
	//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
	//
	//  PURPOSE:  Processes messages for the main window.
	//
	//  WM_DESTROY	- post a quit message and return
	//
	//
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_DESTROY:
			{
				auto element = g_windows.find(hWnd);
				if(element != g_windows.end())
				{
					element->second->closeWindow();
				}
			}
			break;

		case WM_SETFOCUS:
			break ;

		case WM_KILLFOCUS:
			break;

		case WM_SIZE:
			{
				auto element = g_windows.find(hWnd);
				if(element != g_windows.end())
				{
					element->second->updateSize();
				}
			}
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}

	GraphicsWindowD3D11::GraphicsWindowD3D11() : m_hWnd(0), m_width(0), m_height(0), m_shouldClose(false), m_initzialized(false)
	{

	}

	GraphicsWindowD3D11::~GraphicsWindowD3D11(void)
	{
		g_windows.erase(m_hWnd);
		release();
	}

	bool GraphicsWindowD3D11::initialize(ID3D11Device* device, HINSTANCE hInstance, unsigned int width, unsigned int height, const std::string& title, WindowType windowType)
	{
		TCHAR szWindowClass[] = TEXT("D3D11Window");

		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= LoadIcon(hInstance, IDI_APPLICATION);
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
		wcex.lpszMenuName	= 0;
		wcex.lpszClassName	= szWindowClass;
		wcex.hIconSm		= LoadIcon(wcex.hInstance, IDI_APPLICATION);

		RegisterClassEx(&wcex);

		RECT wr = {0, 0, width, height};    // set the size, but not the position
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

		// create the window and use the result as the handle
		m_hWnd = CreateWindowEx(NULL,
                      szWindowClass,			// name of the window class
                      title.c_str(),			// title of the window
                      WS_OVERLAPPEDWINDOW,		// window style
                      CW_USEDEFAULT,			// x-position of the window
                      0,						// y-position of the window
                      wr.right - wr.left,		// width of the window
                      wr.bottom - wr.top,		// height of the windo
                      NULL,						// we have no parent window, NULL
                      NULL,						// we aren't using menus, NULL
                      hInstance,				// application handle
                      NULL);					// used with multiple windows, NULL

		if (!m_hWnd)
		{
			LOG_ERROR("Could create Window");
			return false;
		}
		g_windows.insert(std::pair<HWND, GraphicsWindowD3D11*>(m_hWnd, this));

		updateSize();

		ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(m_hWnd);

		m_context = std::shared_ptr<class RenderContextD3D11>(new RenderContextD3D11());
		m_initzialized = true;
		return m_context->initialize(device, m_hWnd, m_width, m_height, windowType == WindowType::Fullscreen);
	}

	void GraphicsWindowD3D11::release(void)
	{
		if(m_initzialized)
		{
			m_context->release();
			DestroyWindow(m_hWnd);
			LOG_INIT("GraphicsWindowD3D11 released");
		}
		m_initzialized = false;
	}

	RenderContextPtr GraphicsWindowD3D11::getContext() const
	{ 
		return m_context; 
	}

	void GraphicsWindowD3D11::updateSize(void)
	{
		RECT rect;
		if(GetClientRect(m_hWnd, &rect))
		{
			m_width		= rect.right - rect.left;
			m_height	= rect.bottom - rect.top;
		}
		else
		{
			LOG_ERROR("Could not update Windowsize");
		}
	}
}