#include "Texture.h"
#include "Render.h"
#include "RHI.h"
#include "Platform/OpenGL/Graphics/OpenGLTexture2D.h"

namespace BEngine
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Render::GetAPI())
		{
			case RHI::API::None:		BR_CORE_ASSERT(false, "Texture2D Renderer::API::None is not supported!");
			case RHI::API::OpenGL:		return CRef<OpenGLTexture2D>(path);
			case RHI::API::Vulkan:		BR_CORE_ASSERT(false, "Texture2D Renderer::API::Vulkan is not supported!");
			case RHI::API::DX12:		BR_CORE_ASSERT(false, "Texture2D Renderer::API::DX12 is not supported!");
		}

		BR_CORE_ASSERT(false, " Texture2D Unknown RHI ! ");
		return nullptr;
	}
}

