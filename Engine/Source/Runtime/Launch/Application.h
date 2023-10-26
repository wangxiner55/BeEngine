#pragma once
#include "../Engine/Events/Event.h"
#include "../Engine/Window/Window.h"
#include "../Engine/Layer/LayerStack.h"
#include "../Editor/ImguiLayer.h"
#include "Engine/Render/Buffer.h"
#include "Engine/Render/VertexArray.h"

namespace BEngine
{
	class WindowCloseEvent;
	class Shader;


	class BEAR_API Application
	{
	public:

		Application();
		~Application();

		void Run();
	
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow()  { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		std::shared_ptr<Window> m_Window;

		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> m_SqrVertexArray;
		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<Shader> m_Sqrshader;
		
		LayerStack m_LayerStack;



	private:
		static Application* s_Instance;
	};


	Application* CreateApplication();

}
