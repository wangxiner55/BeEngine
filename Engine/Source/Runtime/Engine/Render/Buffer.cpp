#include "Buffer.h"
#include "Render.h"
#include "RHI.h"
#include "Platform/OpenGL/Graphics/OpenGLBuffer.h"

namespace BEngine
{
	



	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Render::GetAPI())
		{
		case RHI::API::None:		BR_CORE_ASSERT(false, "VertexBuffer Renderer::API::None is not supported!");
		case RHI::API::OpenGL:		return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		case RHI::API::Vulkan:		BR_CORE_ASSERT(false, "VertexBuffer Renderer::API::Vulkan is not supported!");
		case RHI::API::DX12:		BR_CORE_ASSERT(false, "VertexBuffer Renderer::API::DX12 is not supported!");
		}

		BR_CORE_ASSERT(false, " VertexBuffer Unknown RendererAPI ! ");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Render::GetAPI())
		{
		case RHI::API::None:		BR_CORE_ASSERT(false, "IndexBuffer Renderer::API::None is not supported!");
		case RHI::API::OpenGL:		return std::make_shared<OpenGLIndexBuffer>(indices, size);
		case RHI::API::Vulkan:		BR_CORE_ASSERT(false, "IndexBuffer Renderer::API::Vulkan is not supported!");
		case RHI::API::DX12:		BR_CORE_ASSERT(false, "IndexBuffer Renderer::API::DX12 is not supported!");
		}

		BR_CORE_ASSERT(false, " IndexBuffer Unknown RendererAPI ! ");
		return nullptr;
	}



}