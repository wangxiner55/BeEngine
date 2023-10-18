#include "Launch/Application.h"
#include "Bear.h"
#include "imgui.h"

class ExampleLayer : public BEngine::Layer
{
public:

	ExampleLayer()
		:BEngine::Layer("Example")
	{

	}

	void OnUpdate() override
	{
		BR_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(BEngine::Event& event) override
	{
		BR_CLIENT_TRACE("{0}", event);
	}

};


class Launch : public BEngine::Application
{
public:
	Launch(){ 
		std::cout << "cons Hive" << std::endl; 
		PushLayer(new ExampleLayer());
	}
	~Launch() { std::cout << "Dre Hive" << std::endl; }

};


BEngine::Application* BEngine::CreateApplication()
{
	return new Launch();
}
