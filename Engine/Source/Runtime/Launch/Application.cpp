#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

#include "../Engine/Events/ApplicationEvent.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Engine/Render/Shader.h"
#include "Engine/Render/Buffer.h"
#include "Engine/Input/Input.h"

namespace BEngine
{
#define EVENT_BIND(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	static GLenum ConverShaderTypeToGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:			return GL_FLOAT;
		case ShaderDataType::Float2:		return GL_FLOAT;
		case ShaderDataType::Float3:		return GL_FLOAT;
		case ShaderDataType::Float4:		return GL_FLOAT;
		case ShaderDataType::Mat3:			return GL_FLOAT;
		case ShaderDataType::Mat4:			return GL_FLOAT;
		case ShaderDataType::Int:			return GL_INT;
		case ShaderDataType::Int2:			return GL_INT;
		case ShaderDataType::Int3:			return GL_INT;
		case ShaderDataType::Int4:			return GL_INT;
		case ShaderDataType::Bool:			return GL_BOOL;
		}

		BR_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}



	Application::Application()
	{
		BR_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(EVENT_BIND(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);



		float vertices[] = {
			 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,// top right
			 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,// bottom right
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
			"void main()\n"
			"{\n"
			"   v_Position = aPos;\n"
			"   v_Color = aCol;\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		std::string fragmentShaderSource = "#version 330 core\n"
			"in vec3 v_Position;\n"
			"in vec4 v_Color;\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(v_Color);\n"
			"}\n\0";




		





		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));


		{
			BufferLayout layout =
			{
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"}
			};

			m_VertexBuffer->SetLayout(layout);
		}



		uint32_t index = 0;
		for (const auto& element : m_VertexBuffer->GetLayout())
		{
			glVertexAttribPointer(
				index,
				ShaderDataTypeCount(element.Type),
				ConverShaderTypeToGLType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				m_VertexBuffer->GetLayout().GetStride(),
				(void*)element.Offset);

			glEnableVertexAttribArray(index);

			index++;
		}


		m_shader.reset(new Shader(vertexShaderSource, fragmentShaderSource));
		
	}

	Application::~Application()
	{
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(EVENT_BIND(Application::OnWindowClose));
		//BR_CORE_INFO("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);

		}

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();

	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();

	}

	void Application::Run()
	{
		while (m_Running)
		{

			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_shader->Bind();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}


			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();



			m_Window->OnUpdate();
			
		}
	}
}
