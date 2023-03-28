#pragma once

// 事件
#include "GLCore/Events/KeyEvent/KeyEvent.h"
#include "GLCore/Events/MouseEvent/MouseEvent.h"
#include "GLCore/Events/ApplicationEvent/ApplicationEvent.h"
#include "GLCore/Events/WindowEvent/WindowEvent.h"

GLCORE_NAMESPACE_BEGIN

// 窗口属性
struct WindowProps
{
	// 窗口标题
	std::string Title;

	// 窗口宽度和高度
	int Width;
	int Height;

	// OpenGL版本号
	int MajorVersion;
	int MinorVersion;

	// 多重采样（用于抗锯齿）
	int Samples;

	// 构造函数
	WindowProps(const std::string& sTitle = "GLCore", int iWidth = 1280, int iHeight = 720, int Samples = 0)
		: Title(sTitle),
		Width(iWidth),
		Height(iHeight),
		MajorVersion(4),
		MinorVersion(3),
		Samples(Samples)
	{
	}
};

// 事件回调函数
using EventCallbackFn = std::function<void(Event&)>;

// 窗口抽象类，单例模式
class Window
{
public:
	// 析构函数（虚函数）
	virtual ~Window() {}

	// 每一帧调用
	virtual void OnUpdate() = 0;

	/********************** 窗口属性 ************************/
	// 获取窗口宽度（纯虚函数）
	virtual unsigned int GetWindowWidth() const = 0;
	// 获取窗口高度（纯虚函数）
	virtual unsigned int GetWindowHeight() const = 0;
	// 设置窗口事件回调函数,平台触发
	virtual void SetEventCallback(const EventCallbackFn& callback) = 0; 
	// 设置垂直同步
	virtual void SetVSync(bool enabled) = 0;
	// 是否开启垂直同步
	virtual bool IsVSync() const = 0;
	// 获取原始窗口
	virtual void* GetNativeWindow()const = 0;

	/********************** 创建窗口 ************************/
	static Ref<Window> Create(const WindowProps& windowPorps = WindowProps());
protected:
	// 构造函数
	Window(const WindowProps& windowPorps);
private:
	// 删除默认构造、拷贝构造和拷贝赋值运算符（用于单例模式）
	Window() = delete;
	Window(Window&) = delete;
	Window& operator=(const Window&) = delete;
protected:
	// 窗口属性
	WindowProps m_WindowProps;
};

GLCORE_NAMESPACE_END