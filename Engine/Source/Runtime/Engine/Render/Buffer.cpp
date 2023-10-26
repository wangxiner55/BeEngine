#include "Buffer.h"
#include "Render.h"
#include "Platform/OpenGL/Graphics/OpenGLBuffer.h"
#include "RendererAPI.h"

namespace BEngine
{
	



	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Render::GetAPI())
		{
		case RendererAPI::API::None:		BR_CORE_ASSERT(false, "VertexBuffer Renderer::API::None is not supported!");
		case RendererAPI::API::OpenGL:		return new OpenGLVertexBuffer(vertices, size);
		case RendererAPI::API::Vulkan:		BR_CORE_ASSERT(false, "VertexBuffer Renderer::API::Vulkan is not supported!");
		case RendererAPI::API::DX12:		BR_CORE_ASSERT(false, "VertexBuffer Renderer::API::DX12 is not supported!");
		}

		BR_CORE_ASSERT(false, " VertexBuffer Unknown RendererAPI ! ");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Render::GetAPI())
		{
		case RendererAPI::API::None:		BR_CORE_ASSERT(false, "IndexBuffer Renderer::API::None is not supported!");
		case RendererAPI::API::OpenGL:		return new OpenGLIndexBuffer(indices, size);
		case RendererAPI::API::Vulkan:		BR_CORE_ASSERT(false, "IndexBuffer Renderer::API::Vulkan is not supported!");
		case RendererAPI::API::DX12:		BR_CORE_ASSERT(false, "IndexBuffer Renderer::API::DX12 is not supported!");
		}

		BR_CORE_ASSERT(false, " IndexBuffer Unknown RendererAPI ! ");
		return nullptr;
	}



}