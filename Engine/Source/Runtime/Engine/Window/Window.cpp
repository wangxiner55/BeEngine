#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Engine/Render/RHI.h"
#include "Engine/Render/Render.h"

namespace BEngine
{

	Uniq<Window> Window::Create(const WindowProps& props)
	{
		switch (Render::GetAPI())
		{
			case RHI::API::None:		BR_CORE_ASSERT(false, "Window Renderer::API::None is not supported!");
			case RHI::API::OpenGL:		return std::make_unique<WindowsWindow>(props);
			case RHI::API::Vulkan:		BR_CORE_ASSERT(false, "Window Renderer::API::Vulkan is not supported!");
			case RHI::API::DX12:		BR_CORE_ASSERT(false, "Window Renderer::API::DX12 is not supported!");
		}

		BR_CORE_ASSERT(false, " Window Unknown RendererAPI ! ");
		return nullptr;
	}

}