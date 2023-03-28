#pragma once

#include "../Event.h"

GLCORE_NAMESPACE_BEGIN

// App
class AppTickEvent : public Event
{
public:
	AppTickEvent() = default;
	// 通过 Event 继承
	EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

// App更新事件
class AppUpdateEvent : public Event
{
public:
	AppUpdateEvent() = default;
	// 通过 Event 继承
	EVENT_CLASS_TYPE(AppUpdate)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

// App渲染事件
class AppRenderEvent : public Event
{
public:
	AppRenderEvent() = default;
	// 通过 Event 继承
	EVENT_CLASS_TYPE(AppRender)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

GLCORE_NAMESPACE_END