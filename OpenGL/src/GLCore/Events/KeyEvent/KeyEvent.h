#pragma once

#include "GLCore/Core/Input/Code/KeyCode.h"
#include "../Event.h"

GLCORE_NAMESPACE_BEGIN

// 键盘事件
class KeyEvent : public Event
{
public:
	// 
	KeyCode GetKeyCode() const;

	// 
	EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)
protected:
	// 构造函数
	KeyEvent(KeyCode uiKeyCode);

	// 
	KeyCode m_uiKeyCode;
};

// 按键按下事件
class KeyPressedEvent :public KeyEvent
{
public:
	// 
	KeyPressedEvent(KeyCode uiKeyCode, bool bRepeat = false);

	// 
	bool IsRepeat()const;

	// 
	std::string ToString()const override;

	// 
	EVENT_CLASS_TYPE(KeyPressed)
private:
	// 
	bool m_bRepeat;
};

// 按键释放事件
class KeyReleasedEvent :public KeyEvent
{
public:
	// 构造函数
	KeyReleasedEvent(KeyCode uiKeyCode);

	// 
	std::string ToString()const override;

	// 
	EVENT_CLASS_TYPE(KeyReleased)
};


// 按键类型事件
class KeyTypedEvent :public KeyEvent
{
public:
	// 
	KeyTypedEvent(KeyCode uiKeyCode);

	// 
	std::string ToString()const override;

	// 
	EVENT_CLASS_TYPE(KeyTyped)
};

GLCORE_NAMESPACE_END