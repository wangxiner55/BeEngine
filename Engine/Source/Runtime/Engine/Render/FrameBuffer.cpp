#include "FrameBuffer.h"
#include "Render.h"
#include "RHI.h"
#include "Platform/OpenGL/Graphics/OpenGLFrameBuffer.h"
namespace BEngine
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Render::GetAPI())
		{
		case RHI::API::None:		BR_CORE_ASSERT(false, "VertexBuffer Renderer::API::None is not supported!");
		case RHI::API::OpenGL:		return  CRef<OpenGLFramebuffer>(spec);
		case RHI::API::Vulkan:		BR_CORE_ASSERT(false, "VertexBuffer Renderer::API::Vulkan is not supported!");
		case RHI::API::DX12:		BR_CORE_ASSERT(false, "VertexBuffer Renderer::API::DX12 is not supported!");
		}

		BR_CORE_ASSERT(false, " VertexBuffer Unknown RendererAPI ! ");
		return nullptr;
	}
}

