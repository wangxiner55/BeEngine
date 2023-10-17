#include "Application.h"
#include "Events/ApplicationEvent.h"


#include "GLFW/glfw3.h"
#include "Bear/log.h"


namespace BEngine
{
#define EVENT_BIND(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(EVENT_BIND(Application::OnEvent));
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
		BR_CORE_INFO("{0}", e);
	}

	void Application::Run()
	{
		while (m_Running)
		{

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
			
		}
	}
}
