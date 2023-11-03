#pragma once

#include "RHI.h"
#include "Shader.h"

namespace BEngine
{
	class Camera;

	class Render
	{
	public:

		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(Ref<Camera>& camera);
		static void EndScene();


		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1));


		inline static RHI::API GetAPI() { return RHI::GetAPI(); }

	private:

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			glm::mat4 MVPMatrix;
			glm::mat4 transform;
		};

		static SceneData* m_SceneData;
	};
}