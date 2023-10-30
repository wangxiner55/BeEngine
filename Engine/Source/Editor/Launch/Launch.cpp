#include "Launch/Application.h"
#include "Bear.h"
#include "imgui.h"
#include "glm/glm.hpp"
#include "Engine/Geo/Geo.h"
#include "Engine/Render/Camera.h"


class ExampleLayer : public BEngine::Layer
{
public:

	ExampleLayer()
		:m_CameraPosition(0.f)
	{
		float vertices[] = {
			 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,// top right
			 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,// bottom right
			 0.0f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,// bottom left
			 0.0f,  0.5f, 0.0f,  0.5f, 0.5f, 0.5f, 1.0f // top left 
		};

		float sqrvertices[] = {
			 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,// top right
			 0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,// bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,// bottom left
			-0.5f,  0.5f, 0.0f,  0.5f, 0.5f, 0.5f, 1.0f // top left 
		};

		unsigned int indices[] = {
			0, 1, 3, // 第一个三角形
			1, 2, 3  // 第二个三角形
		};


		std::string vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec4 aCol;\n"
			"out vec3 v_Position;\n"
			"out vec4 v_Color;\n"
			"uniform mat4 u_ViewProjection;"
			"void main()\n"
			"{\n"
			"   v_Position = aPos;\n"
			"   v_Color = aCol;\n"
			"   gl_Position = u_ViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		std::string fragmentShaderSource = "#version 330 core\n"
			"in vec3 v_Position;\n"
			"in vec4 v_Color;\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(v_Color);\n"
			"}\n\0";



		std::string SqrvertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec4 aCol;\n"
			"out vec3 v_Position;\n"
			"out vec4 v_Color;\n"
			"uniform mat4 u_ViewProjection;"
			"void main()\n"
			"{\n"
			"   v_Position = aPos;\n"
			"   v_Color = aCol;\n"
			"   gl_Position = u_ViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		std::string SqrfragmentShaderSource = "#version 330 core\n"
			"in vec3 v_Position;\n"
			"in vec4 v_Color;\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0,1.0,0.0,1.0);\n"
			"}\n\0";


		m_VertexArray.reset(BEngine::VertexArray::Create());

		std::shared_ptr<BEngine::VertexBuffer> vertexBuffer;
		std::shared_ptr<BEngine::IndexBuffer> indexBuffer;
		vertexBuffer.reset(BEngine::VertexBuffer::Create(BEngine::boxVertex, sizeof(BEngine::boxVertex)));
		indexBuffer.reset(BEngine::IndexBuffer::Create(BEngine::boxIndex, sizeof(BEngine::boxIndex) / sizeof(uint32_t)));

		{
			BEngine::BufferLayout layout =
			{
				{BEngine::ShaderDataType::Float3, "a_Position"},
				{BEngine::ShaderDataType::Float4, "a_Color"}
			};

			vertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_shader.reset(new BEngine::Shader(vertexShaderSource, fragmentShaderSource));



		glEnable(GL_DEPTH_TEST);

		//m_SqrVertexArray.reset(BEngine::VertexArray::Create());

		//std::shared_ptr<BEngine::VertexBuffer> SqrvertexBuffer;
		//std::shared_ptr<BEngine::IndexBuffer> SqrindexBuffer;
		//SqrvertexBuffer.reset(BEngine::VertexBuffer::Create(sqrvertices, sizeof(sqrvertices)));
		//SqrindexBuffer.reset(BEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		//{
		//	BEngine::BufferLayout layout =
		//	{
		//		{BEngine::ShaderDataType::Float3, "a_Position"},
		//		{BEngine::ShaderDataType::Float4, "a_Color"}
		//	};

		//	SqrvertexBuffer->SetLayout(layout);
		//}

		//m_SqrVertexArray->AddVertexBuffer(SqrvertexBuffer);
		//m_SqrVertexArray->SetIndexBuffer(SqrindexBuffer);

		//m_Sqrshader.reset(new BEngine::Shader(SqrvertexShaderSource, SqrfragmentShaderSource));
	}

	void OnUpdate() override
	{
		BEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		BEngine::RenderCommand::Clear();

		BEngine::Render::BeginScene(m_Camera);
		//m_Camera->SetPosition(m_CameraPosition);
		//m_Camera->SetRotation(45);
		m_Camera->Tick();
		std::cout << m_Camera->GetPosition().r << m_Camera->GetPosition().g << m_Camera->GetPosition().b << std::endl;
		//BEngine::Render::Submit(m_SqrVertexArray, m_Sqrshader);


		BEngine::Render::Submit(m_VertexArray, m_shader);

		BEngine::Render::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(BEngine::Event& event) override
	{
		//BEngine::EventDispatcher dispatcher(event);
		//dispatcher.Dispatch<BEngine::KeyPressedEvent>(EVENT_BIND(ExampleLayer::OnKeyPressedEvent));


		m_Camera->OnEvent(event);


	}

	bool OnKeyPressedEvent(BEngine::KeyPressedEvent& event)
	{
	}


private:


	
	std::shared_ptr<BEngine::VertexArray> m_VertexArray;
	std::shared_ptr<BEngine::VertexArray> m_SqrVertexArray;
	std::shared_ptr<BEngine::Shader> m_shader;
	std::shared_ptr<BEngine::Shader> m_Sqrshader;


	std::shared_ptr<BEngine::Camera> m_Camera = BEngine::Camera::Create(BEngine::CameraType::PerspectiveCamera);
	glm::vec3 m_CameraPosition = glm::vec3(0.0,0.0,3.0);
	float m_CameraSpeed = 0.1;
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
