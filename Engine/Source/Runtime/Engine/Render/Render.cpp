#include "Render.h"
#include "RenderCommand.h"
#include "Camera.h"

namespace BEngine
{

	Render::SceneData* Render::m_SceneData = new Render::SceneData;


	void Render::BeginScene(std::shared_ptr<Camera>& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera->GetMVPMatrix();
		m_SceneData->MVPMatrix = camera->GetMVPMatrix();
	}

	void Render::EndScene()
	{
	}

	void Render::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform )
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->MVPMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndex(vertexArray);
	}

}


