#pragma once
#include "Core/Base/Core.h"

#include "Engine/Events/Event.h"

namespace BEngine
{
	struct WindowProps
	{
		std::string _title;
		uint32_t _width;
		uint32_t _height;

		
		WindowProps(const std::string& title = "Bear",
					uint32_t width = 1280, 
					uint32_t height = 720)
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
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;


		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;

		static Uniq<Window> Create(const WindowProps& props = WindowProps());
	private:


	};




}