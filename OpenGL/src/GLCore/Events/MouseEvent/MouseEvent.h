#pragma once

#include "GLCore/Core/Input/Code/MouseCode.h"
#include "../Event.h"

GLCORE_NAMESPACE_BEGIN

// 鼠标移动事件
class MouseMovedEvent :public Event
{
public:
	MouseMovedEvent(float fMouseX, float fMouseY);
	float GetMouseX() const;
	float GetMouseY() const;
	std::string ToString()const override;
	EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
	float m_fMouseX;
	float m_fMouseY;
};

// 鼠标滚动事件
class MouseScrolledEvent :public Event
{
public:
	MouseScrolledEvent(float fXOffset, float fYOffset);
	float GetXOffset()const;
	float GetYOffset()const;
	std::string ToString()const override;
	EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
	float m_fXOffset;
	float m_fYOffset;
};

// 鼠标按钮事件
class MouseButtonEvent :public Event
{
public:
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton);
	MouseCode GetMouseButton()const;
protected:
	MouseButtonEvent(MouseCode uiMouseCode);
	MouseCode m_uiMouseCode;
};

// 鼠标按钮按下事件
class MouseButtonPressedEvent :public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(MouseCode uiMouseCode);
	std::string ToString()const override;
	EVENT_CLASS_TYPE(MouseButtonPressed)
};

// 鼠标按钮释放事件
class MouseButtonReleasedEvent :public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(MouseCode uiMouseCode);
	std::string ToString()const override;
	EVENT_CLASS_TYPE(MouseButtonReleased)
};


GLCORE_NAMESPACE_END