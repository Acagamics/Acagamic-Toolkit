#pragma once
#include <memory>

namespace ACTK
{
namespace Renderer
{
	enum class Texture2DFormat : char
	{
		RedGreenBlue8,
		RedGreenBlue16,
		RedGreenBlueAlpha8,
		RedGreenBlue10A2,
		RedGreenBlueAlpha16,
		Depth16,
		Depth24,
		Red8,
		Red16,
		RedGreen8,
		RedGreen16,
		Red16f,
		Red32f,
		RedGreen16f,
		RedGreen32f,
		Red8i,
		Red8ui,
		Red16i,
		Red16ui,
		Red32i,
		Red32ui,
		RedGreen8i,
		RedGreen8ui,
		RedGreen16i,
		RedGreen16ui,
		RedGreen32i,
		RedGreen32ui,
		RedGreenBlueAlpha32f,
		RedGreenBlue32f,
		RedGreenBlueAlpha16f,
		RedGreenBlue16f,
		Depth24Stencil8,
		Red11fGreen11fBlue10f,
		RedGreenBlue9E5,
		SRedGreenBlue8,
		SRedGreenBlue8Alpha8,
		Depth32f,
		Depth32fStencil8,
		RedGreenBlueAlpha32ui,
		RedGreenBlue32ui,
		RedGreenBlueAlpha16ui,
		RedGreenBlue16ui,
		RedGreenBlueAlpha8ui,
		RedGreenBlue8ui,
		RedGreenBlueAlpha32i,
		RedGreenBlue32i,
		RedGreenBlueAlpha16i,
		RedGreenBlue16i,
		RedGreenBlueAlpha8i,
		RedGreenBlue8i
	};

	class Texture2DDescription
	{
	public:
		Texture2DDescription(int width, int height, Texture2DFormat format, bool generateMipmaps = false) : 
			m_width(), m_height(),
			m_format(),
			m_generateMipmaps()
		{}
		~Texture2DDescription(){}

	private:
		int m_width, m_height;
		Texture2DFormat m_format;
		bool m_generateMipmaps;
	};

	class ITexture2D
	{
		virtual Texture2DFormat getDiscription() = 0;
	};

	typedef std::shared_ptr<ITexture2D> Texture2DPtr;
}
}