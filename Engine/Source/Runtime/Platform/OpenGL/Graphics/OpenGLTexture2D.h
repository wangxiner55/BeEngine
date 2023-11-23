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

		inline virtual uint32_t GetWidth() const override  { return m_Width; }
		inline virtual uint32_t GetHeight() const override  { return m_Height; }
		inline virtual uint32_t GetRenderID() const override { return m_RendererID; }
		inline virtual TextureType GetType() const override { return m_type; }
		inline virtual std::string GetPath() const override { return m_path; }
		inline virtual void SetType(const TextureType& type) override { m_type = type; }
		inline virtual void SetPath(const std::string& repath) override { m_path = repath; }

		virtual void Bind(uint32_t slot = 0) const;
	private:

		TextureType m_type = TextureType::Diffuse;
		std::string m_path;

		uint32_t m_Width, m_Height;
		uint32_t m_RendererID = -1;
	};



}