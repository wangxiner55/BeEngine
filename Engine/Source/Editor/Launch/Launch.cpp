#include "Launch/Application.h"
#include "Bear.h"
#include "imgui.h"
#include "glm/glm.hpp"


class ExampleLayer : public BEngine::Layer
{
public:

	ExampleLayer()
		:BEngine::Layer("Example")
	{
		glm::abs(5);
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

	}
	~Launch() { }

};


BEngine::Application* BEngine::CreateApplication()
{
	return new Launch();
}
