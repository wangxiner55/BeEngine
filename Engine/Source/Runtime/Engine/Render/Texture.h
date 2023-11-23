#pragma once


namespace BEngine
{
	enum class TextureType : UINT8
	{
		Diffuse = 0, Specular, Normal, Height
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRenderID() const = 0;
		virtual TextureType GetType() const = 0;
		virtual std::string GetPath() const = 0;
		virtual void SetType(const TextureType& type) = 0;
		virtual void SetPath(const std::string& repath) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

	};


	class Texture2D : public Texture
	{

	public:
		
		static Ref<Texture2D> Create(const std::string& path);


	};



}