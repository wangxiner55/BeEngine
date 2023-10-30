#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

#include "../Engine/Events/ApplicationEvent.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Engine/Render/Shader.h"
#include "Engine/Render/Buffer.h"
#include "Engine/Input/Input.h"
#include "Engine/Render/Render.h"
#include "Engine/Render/RenderCommand.h"


#include "Engine/Render/OrthographicCamera.h"


namespace BEngine
{
#define EVENT_BIND(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	



	Application::Application()
	{
		BR_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(EVENT_BIND(Application::OnEvent));
		m_Window->SetVSync(false);

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);

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
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(timestep);
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
