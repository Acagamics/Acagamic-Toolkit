#pragma once
#include "ACTK.h"
#include <memory>
#include <Windows.h>
#include "ClearState.h"

namespace ACTK
{
namespace Renderer
{
	enum class PrimitiveType : char
	{
		POINTS,
		LINE,
		LINES,
		LINE_STRIP,
		LINE_LOOP,
		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
		QUADS,
		QUAD_STRIP,
		POLYGON
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

		virtual void VDraw(PrimitiveType type ,float* vertices, unsigned int count) = 0;

		virtual void VSwapBuffers(void) = 0;
	};

	typedef std::shared_ptr<IRenderContext> RenderContextPtr;

}}