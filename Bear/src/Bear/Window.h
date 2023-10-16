#pragma once
#include "../PreComHead.h"

#include "Core.h"
#include "Events/Event.h"

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
		

		// Interface representing a desktop system base window
		class BEAR_API Window
		{
		public:

			//using EventCallbackFn = 



		};

	};






}