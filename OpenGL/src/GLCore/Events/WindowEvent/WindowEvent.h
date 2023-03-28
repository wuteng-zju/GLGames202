#pragma once

#include "../Event.h"

GLCORE_NAMESPACE_BEGIN

// 窗口大小调整事件
class WindowResizedEvent : public Event
{
public:
	WindowResizedEvent(unsigned int uiWidth, unsigned int uiHeight);
	unsigned int GetWidth()const;
	unsigned int GetHeight()const;
	std::string ToString() const override;

	// 通过 Event 继承
	EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
private:
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;
};

// 窗口关闭事件
class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;
	// 通过 Event 继承
	EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

GLCORE_NAMESPACE_END