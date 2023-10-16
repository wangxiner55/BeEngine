#pragma once
#include "Core.h"
#include "Events/Event.h"

namespace BEngine
{
	class BEAR_API Application
	{
	public:

		Application();
		~Application();

		void Run();
		

	};


	Application* CreateApplication();

}
