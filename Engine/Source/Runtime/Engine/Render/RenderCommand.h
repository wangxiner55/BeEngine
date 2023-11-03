#pragma once
#include "RHI.h"

namespace BEngine
{


	class RenderCommand
	{


	public:

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RHI->SetViewport(x, y, width, height);
		}

		inline static void Init()
		{
			s_RHI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RHI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RHI->Clear();
		}


		inline static void DrawIndex(const Ref<VertexArray>& vertexArray)
		{
			s_RHI->DrawIndexed(vertexArray);
		}


	private:
		static RHI* s_RHI;
	};




}