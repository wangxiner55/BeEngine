#include "Render.h"
#include "RenderCommand.h"

namespace BEngine
{

	Render::SceneData* Render::m_SceneData = new Render::SceneData;


	void Render::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectMatrix();
	}

	void Render::EndScene()
	{
	}

	void Render::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndex(vertexArray);
	}

}


