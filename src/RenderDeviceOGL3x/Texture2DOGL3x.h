#pragma once
#include "ITexture2D.h"

namespace ACTK
{

	using namespace Renderer;

	class Texture2DOGL3x : public ITexture2D
	{
	public:
		Texture2DOGL3x();
		~Texture2DOGL3x();

		Texture2DFormat getDescription();

	private:
		Texture2DDescription m_description;
		int m_handle;
	};
}