#pragma once
#ifndef EDITOR
#define EDITOR


//#include <Bear.h>
#include <Engine/Render/Shader.h>
#include <Engine/Render/VertexArray.h>
#include <Engine/Render/FrameBuffer.h>
#include <Engine/Framework/Component/Camera/Camera.h>
#include <Engine/Layer/Layer.h>
#include <Engine/Render/Texture.h>



namespace BEngine
{
	class  EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() {}

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

	private:
		Ref<BEngine::ShaderLibrary> m_ShaderLibrary;
		Ref<BEngine::VertexArray> m_VertexArray;
		Ref<BEngine::Texture2D> m_Texture2D;
		Ref<BEngine::Framebuffer> m_Framebuffer;

		BEngine::Ref<BEngine::Camera> m_Camera;
		glm::vec3 m_CameraPosition = glm::vec3(0.0, 0.0, 3.0);
		glm::vec3 m_color = glm::vec3(1.0, 1.0, 1.0);
		glm::vec2 m_ViewportSize = {0.0,0.};
	};
}


#endif // !EDITOR