#include "Launch/Application.h"
#include "Bear.h"
#include "imgui.h"
#include "glm/glm.hpp"
#include "Engine/Geo/Geo.h"
#include "Engine/Render/Camera.h"
#include "glm/gtc/type_ptr.hpp"
#include "Platform/OpenGL/Graphics/OpenGLShader.h"
#include "Engine/Render/Texture.h"
#include "Engine/Render/Shader.h"


class ExampleLayer : public BEngine::Layer
{
public:

	ExampleLayer()
		:m_CameraPosition(0.f)
	{
		m_VertexArray = BEngine::VertexArray::Create();

		BEngine::Ref<BEngine::VertexBuffer> vertexBuffer;
		BEngine::Ref<BEngine::IndexBuffer> indexBuffer;

		
		vertexBuffer.reset(BEngine::VertexBuffer::Create(BEngine::boxVertex, sizeof(BEngine::boxVertex)));
		indexBuffer.reset(BEngine::IndexBuffer::Create(BEngine::boxIndex, sizeof(BEngine::boxIndex) / sizeof(uint32_t)));

		{
			BEngine::BufferLayout layout =
			{
				{BEngine::ShaderDataType::Float3, "a_Position"},
				{BEngine::ShaderDataType::Float4, "a_Color"},
				{BEngine::ShaderDataType::Float2, "a_UV"}
			};

			vertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string filepath = "D:\\Engine\\BeEngine\\Engine\\Assets\\Shader\\Texture.glsl";

		m_ShaderLibrary->Load(filepath);
		m_Texture2D = BEngine::Texture2D::Create("D:\\Engine\\BeEngine\\Engine\\Assets\\Textures\\floor_2k.png");
		auto Shader = m_ShaderLibrary->Get("Texture");
		std::dynamic_pointer_cast<BEngine::OpenGLShader>(Shader)->UploadUniformInt("u_Texture", 0);
		
		

	}

	void OnUpdate(BEngine::Timestep ts) override
	{
		//BR_CLIENT_TRACE("Delta time : {0}s ({1}ms)", ts.GetSeconds(),ts.GetMilliseconds());
		BEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		BEngine::RenderCommand::Clear();

		BEngine::Render::BeginScene(m_Camera);

		m_Camera->SetPosition({0,0,-5});
		m_Camera->Tick(ts);
		m_Texture2D->Bind();



		auto Shader = m_ShaderLibrary->Get("Texture");
		std::dynamic_pointer_cast<BEngine::OpenGLShader>(Shader)->UploadUniformFloat3("u_Color", m_color);

		BEngine::Render::Submit(m_VertexArray, Shader);
		BEngine::Render::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_color));
		ImGui::SliderFloat("Rotate Speed", &m_Camera->GetRotationSpeed(), 0.0f, 200.0f, "%.0f");
		ImGui::SliderFloat("Move Speed", &m_Camera->GetMovementSpeed(), 0.0f, 200.0f, "%.0f");
		ImGui::End();
	}

	void OnEvent(BEngine::Event& event) override
	{
		m_Camera->OnEvent(event);
	}

	bool OnKeyPressedEvent(BEngine::KeyPressedEvent& event)
	{
	}


private:


	
	BEngine::Ref<BEngine::ShaderLibrary> m_ShaderLibrary = std::make_shared<BEngine::ShaderLibrary>();
	BEngine::Ref<BEngine::VertexArray> m_VertexArray;
	BEngine::Ref<BEngine::Texture2D> m_Texture2D;


	BEngine::Ref<BEngine::Camera> m_Camera = BEngine::Camera::Create(BEngine::CameraType::PerspectiveCamera);
	glm::vec3 m_CameraPosition = glm::vec3(0.0,0.0,3.0);
	float m_CameraSpeed = 0.1;
	glm::vec3 m_color = glm::vec3(1.0, 1.0, 1.0);
};


class Launch : public BEngine::Application
{
public:
	Launch(){ 
		PushLayer(new ExampleLayer());
	}
	~Launch() { }

};


BEngine::Application* BEngine::CreateApplication()
{
	return new Launch();
}
