#pragma once
#include "ITexture2D.h"
#include "TypeConverterOGL3x.h"

namespace ACTK
{

	using namespace Renderer;

	class Texture2DOGL3x : public ITexture2D
	{
	public:

		// Move this to according .cpp.
		Texture2DOGL3x(const int location, const Texture2DDescription description);
		~Texture2DOGL3x();

		Texture2DDescription GetDescription() { return m_description; }

	private:
		Texture2DDescription m_description;
		int m_location;
		unsigned int* m_handle;

	};
}