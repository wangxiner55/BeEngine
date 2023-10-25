#pragma once


namespace BEngine
{

	enum class RendererAPI
	{
		None = 0, OpenGL = 1, Vulkan = 2, DX12 = 3
	};

	class Render
	{
	public:
		inline static RendererAPI GetAPI() { return s_RenderAPI; }

	private:
		static RendererAPI s_RenderAPI;


	};
}