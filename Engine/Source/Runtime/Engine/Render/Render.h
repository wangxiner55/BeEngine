#pragma once

#include "RendererAPI.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace BEngine
{
	class Camera;

	class Render
	{
	public:

		static void BeginScene(std::shared_ptr<Camera>& camera);
		static void EndScene();


		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);


		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			glm::mat4 MVPMatrix;
		};

		static SceneData* m_SceneData;
	};
}