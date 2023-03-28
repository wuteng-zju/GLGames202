#include "pch.h"

// Window平台下实现的窗口类
#include "Platform/Windows/WindowsWindow/WindowsWindow.h"

GLCORE_NAMESPACE_BEGIN

// 创建窗口
Ref<Window> Window::Create(const WindowProps& windowPorps)
{
// 如果当前编译平台是Windows，则使用WindowsWindow创建窗口
#ifdef GLCORE_PLATFORM_WINDOWS
	return CreateRef<WindowsWindow>(windowPorps);
#else
	GLCORE_ASSERT(false, "Unkown platform");
	return nullptr;
#endif // GLCORE_PLATFORM_WINDOW
}

// 构造函数
Window::Window(const WindowProps& windowPorps) :
	m_WindowProps(windowPorps)
{
}

GLCORE_NAMESPACE_END