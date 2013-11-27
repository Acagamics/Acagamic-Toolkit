#pragma once
#include "ACTK.h"
#include "IRenderDevice.h"
#include <Windows.h>
#include <string>

namespace ACTK {

	class RenderDeviceOGL3x : public IRenderDevice
	{
	public:
		RenderDeviceOGL3x(HINSTANCE hInstance);
		~RenderDeviceOGL3x(void){ release(); }
		void release(void);

		// Creates Window and handles Resize and Destruction itselfs
		GraphicsWindowPtr	createWindow(unsigned int width, unsigned int height, const std::string& title, WindowType windowType);

		ShaderProgramPtr	createShaderProgram(const std::string& VertexShaderSource, const std::string& FragementShaderSource);
		ShaderProgramPtr	createShaderProgram(const std::string& VertexShaderSource, const std::string& GeometryShaderSource, const std::string& FragementShaderSource);

	private:
		//you shall not copy
		RenderDeviceOGL3x(RenderDeviceOGL3x&){} 
		RenderDeviceOGL3x& operator=( const RenderDeviceOGL3x& ) {return *this;}

		HINSTANCE m_hInstance;
	};

}