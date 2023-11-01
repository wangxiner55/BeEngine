#include "VertexArray.h"

#include "Platform/OpenGL/Graphics/OpenGLVertexArray.h"
#include "Render.h"
#include "RendererAPI.h"

namespace BEngine
{

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Render::GetAPI())
		{
		case RendererAPI::API::None:		BR_CORE_ASSERT(false, "VertexArray Renderer::API::None is not supported!");
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLVertexArray>();
		case RendererAPI::API::Vulkan:		BR_CORE_ASSERT(false, "VertexArray Renderer::API::Vulkan is not supported!");
		case RendererAPI::API::DX12:		BR_CORE_ASSERT(false, "VertexArray Renderer::API::DX12 is not supported!");
		}

		BR_CORE_ASSERT(false, " VertexArray Unknown RendererAPI ! ");
		return nullptr;

	}





}