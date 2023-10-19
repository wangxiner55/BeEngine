#pragma once
#include "Core/Base/Core.h"

#include "Engine/Events/Event.h"

namespace BEngine
{
	struct WindowProps
	{
		std::string _title;
		unsigned int _width;
		unsigned int _height;

		
		WindowProps(const std::string& title = "Bear",
					const unsigned int& width = 1280, 
					const unsigned int& height = 720)
			:_title(title), _width(width), _height(height)
		{
		}
		

	};

	// Interface representing a desktop system base window
	class BEAR_API Window
	{
	public:

		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window(){}
		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;


		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;


		static Window* Create(const WindowProps& props = WindowProps());
	private:


	};




}