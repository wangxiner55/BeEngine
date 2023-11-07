#include "VertexArray.h"

#include "Platform/OpenGL/Graphics/OpenGLVertexArray.h"
#include "Render.h"
#include "RHI.h"

namespace BEngine
{

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Render::GetAPI())
		{
		case RHI::API::None:		BR_CORE_ASSERT(false, "VertexArray Renderer::API::None is not supported!");
		case RHI::API::OpenGL:		return CRef<OpenGLVertexArray>();
		case RHI::API::Vulkan:		BR_CORE_ASSERT(false, "VertexArray Renderer::API::Vulkan is not supported!");
		case RHI::API::DX12:		BR_CORE_ASSERT(false, "VertexArray Renderer::API::DX12 is not supported!");
		}

		BR_CORE_ASSERT(false, " VertexArray Unknown RendererAPI ! ");
		return nullptr;

	}





}