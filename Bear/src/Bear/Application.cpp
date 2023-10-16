#include "Application.h"
#include "Events/ApplicationEvent.h"

//#include "Events/ApplicationEvent.h"
#include "log.h"



namespace BEngine
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(100, 100);
		std::cout << "Hello World" << std::endl;
	}
}
