#include "Render.h"
#include "RenderCommand.h"
#include "Camera.h"
#include "Platform/OpenGL/Graphics/OpenGLShader.h"

namespace BEngine
{

	Render::SceneData* Render::m_SceneData = new Render::SceneData;

	void Render::Init()
	{
		RenderCommand::Init();
	}

	void Render::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Render::BeginScene(Ref<Camera>& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera->GetMVPMatrix();
		m_SceneData->MVPMatrix = camera->GetMVPMatrix();
	}

	void Render::EndScene()
	{
	}

	void Render::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform )
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->MVPMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndex(vertexArray);
	}

}


