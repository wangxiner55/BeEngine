#include "Texture.h"
#include "Render.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/Graphics/OpenGLTexture2D.h"

namespace BEngine
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Render::GetAPI())
		{
			case RendererAPI::API::None:		BR_CORE_ASSERT(false, "Texture2D Renderer::API::None is not supported!");
			case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLTexture2D>(path);
			case RendererAPI::API::Vulkan:		BR_CORE_ASSERT(false, "Texture2D Renderer::API::Vulkan is not supported!");
			case RendererAPI::API::DX12:		BR_CORE_ASSERT(false, "Texture2D Renderer::API::DX12 is not supported!");
		}

		BR_CORE_ASSERT(false, " Texture2D Unknown RendererAPI ! ");
		return nullptr;
	}
}

