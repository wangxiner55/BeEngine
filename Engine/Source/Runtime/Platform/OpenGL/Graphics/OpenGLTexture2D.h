#pragma once
#include "Engine/Render/Texture.h"
#include "ThirdParty/stb_Image/stb_image.h"

namespace BEngine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();
		virtual uint32_t GetWidth() const override  { return m_Width; }
		virtual uint32_t GetHeight() const override  { return m_Height; }
		virtual uint32_t GetRenderID() const override { return m_RendererID; }

		virtual void Bind(uint32_t slot = 0) const;
	private:

		std::string m_path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};



}