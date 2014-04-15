#pragma once
#include "ACTK.h"
#include <memory>
#include <Windows.h>
#include "ClearState.h"
#include "IShaderProgram.h"

namespace ACTK
{
namespace Renderer
{
	enum class PrimitiveType : char
	{
		Points, 
		LineStrip, 
		LineLoop, 
		Lines, 
		LineStripAdjacency, 
		LinesAdjacency, 
		TriangleStrip, 
		TriangleFan, 
		Triangles, 
		TriangleStripAdjacency, 
		TrianglesAdjacency, 
		Patches
	};

	class IRenderContext
	{
	public:
		virtual ~IRenderContext(){}

		// =========================================================================
		// INIT/RELEASE STUFF:
		// =========================================================================
		virtual void VRelease(void) = 0;

		// =========================================================================
		// RENDERING STUFF:
		// =========================================================================
		virtual void VClear(const ClearState& clearState) = 0;

		virtual void VDraw(PrimitiveType type ,float* vertices, ShaderProgramPtr shaderProgram, unsigned int count) = 0;

		virtual void VSwapBuffers(void) = 0;
	};

	typedef std::shared_ptr<IRenderContext> RenderContextPtr;

}}