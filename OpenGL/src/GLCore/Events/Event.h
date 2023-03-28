#pragma once
#include "pch.h"

GLCORE_NAMESPACE_BEGIN

// 事件类型
enum class EventType
{
	// 无事件
	None = 0,
	// 窗口操作
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	// App操作
	AppTick, AppUpdate, AppRender,
	// 键盘操作（按下某个键，释放某个键，键入某个键）
	KeyPressed, KeyReleased, KeyTyped,
	// 鼠标操作
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

// 事件类别：每一个二进制位对应一种类别,支持一种Event对应多个EventCategory，最多扩展支持64种事件类别
enum EventCategory
{
	// 无事件
	None = 0,
	// App事件
	EventCategoryApplication = BIT(0),
	// 输入事件
	EventCategoryInput = BIT(1),
	// 键盘事件
	EventCategoryKeyBoard = BIT(2),
	// 鼠标事件
	EventCategoryMouse = BIT(3),
	// 鼠标按钮事件
	EventCategoryMouseButton = BIT(4)
};

// 事件类型
#define EVENT_CLASS_TYPE(type) \
	static EventType GetStaticType(){return EventType::##type; }\
	virtual EventType GetEventType()const override {return GetStaticType(); }\
	virtual const char* GetName()const override {return #type;}

// 事件类别
#define EVENT_CLASS_CATEGORY(category) \
	virtual int GetCategoryFlags() const override { return category; }

// Event类
class Event
{
public:
	// 析构函数
	virtual ~Event() = default;

	// //获取事件类型（纯虚函数）
	virtual EventType GetEventType() const = 0;

	// 获取该事件的名称（纯虚函数）
	virtual const char* GetName() const = 0;

	// 获取该事件所属的事件类别（可多个）（纯虚函数）
	virtual int GetCategoryFlags() const = 0;
	
	// 方便打印调试（纯虚函数）
	virtual std::string ToString() const { return GetName(); }

	// 判断该事件是否属于某一类别
	inline bool IsInCategory(EventCategory category)
	{
		// 将该事件所属的事件类别与输入类别进行与运算
		return GetCategoryFlags() & category;
	}
public:
	// 事件分发一次处理完成标记，可用来阻止事件向下传递
	bool Handle = false;

};

// 事件分发类，用于根据事件类型的不同，调用不同的函数
class EventDispatcher
{
	// EventFn存储了一个输入为任意类型的引用，返回值为bool的函数指针
	template<typename T>
	using EventFn = std::function<bool(T&)>;
public:
	// 构造函数
	EventDispatcher(Event& event) :m_event(event)
	{

	}

	// 接收一个EventFn类型的函数指针
	template<typename T>
	bool Dispatch(EventFn<T> func)
	{
		// 如果当前事件属于这个事件类别
		if (m_event.GetEventType() == T::GetStaticType())
		{
			m_event.Handle |= func(static_cast<T&>(m_event));
			return true;
		}
		return false;
	}
private:
	// 事件
	Event& m_event;
};

// 重载输出运算符（可以输出事件的名称）
inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}

GLCORE_NAMESPACE_END