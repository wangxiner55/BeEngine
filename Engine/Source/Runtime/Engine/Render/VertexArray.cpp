#include "VertexArray.h"

#include "Platform/OpenGL/Graphics/OpenGLVertexArray.h"
#include "Render.h"

namespace BEngine
{

	VertexArray* VertexArray::Create()
	{
		switch (Render::GetAPI())
		{
		case RendererAPI::None:		BR_CORE_ASSERT(false, "VertexArray Renderer::API::None is not supported!");
		case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		case RendererAPI::Vulkan:	BR_CORE_ASSERT(false, "VertexArray Renderer::API::Vulkan is not supported!");
		case RendererAPI::DX12:		BR_CORE_ASSERT(false, "VertexArray Renderer::API::DX12 is not supported!");
		}

		BR_CORE_ASSERT(false, " VertexArray Unknown RendererAPI ! ");
		return nullptr;

	}





}