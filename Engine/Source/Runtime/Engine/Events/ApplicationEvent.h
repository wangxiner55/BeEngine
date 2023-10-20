#pragma once
#include "Event.h"

namespace BEngine
{
	class BEAR_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
		:m_width(width), m_height(height){}

		inline  unsigned int GetWidth() const { return m_width; }
		inline  unsigned int GetHeight() const { return m_height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", ,," << m_height;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowResize)
		
	private:
		unsigned int m_width, m_height;
	};


	class BEAR_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowClose";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

	class BEAR_API APPTickEvent : public Event
	{
	public:
		APPTickEvent(){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Tick";
			return ss.str();
		}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

	class BEAR_API APPRenderEvent : public Event
	{
	public:
		APPRenderEvent() {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Render";
			return ss.str();
		}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}