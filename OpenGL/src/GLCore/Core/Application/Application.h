#pragma once

// 窗口
#include "GLcore/Core/Window/Window.h"
// 层栈
#include "GLCore/Core/Layer/LayerStack/LayerStack.h"
// ImGui
 #include "GLCore/ImGui/ImGuiLayer.h"

GLCORE_NAMESPACE_BEGIN

class Application
{
public:
	// 获取Application
	static Ref<Application> GetApplication();

	static void CreateApplication();

	// 运行Application
	void Run();

	// 构造函数
	Application(const std::string& name, int width, int height, int samples);

	// 析构函数
	virtual ~Application();

	// 关闭应用
	void Close();

	// 事件相关
	void OnEvent(Event& event);
	void BlockEvents(bool bBlock);

	// 窗口相关
	int GetWindowWidth() const;
	int GetWindowHeight() const;
	const Ref<Window>& GetWindow()const;

	// Layer相关
	void PushLayer(Ref<Layer> spLayer);
	void PushOverlay(Ref<Layer> spLayer);
private:
	// 初始化
	void Init();
	Application(Application&) = delete;
	Application& operator=(const Application&) = delete;
private:
	// a事件
	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
	bool OnMouseMovedEvent(MouseMovedEvent& event);
	bool OnMouseScrolledEvent(MouseScrolledEvent& event);

	bool OnKeyPressedEvent(KeyPressedEvent& event);
	bool OnKeyReleasedEvent(KeyReleasedEvent& event);
	bool OnKyeTypedEvent(KeyEvent& event);

	bool OnWindowResizedEvent(WindowResizedEvent& event);
	bool OnWindowClosedEvent(WindowCloseEvent& e);
private:
	// 当前App是否在运行
	bool m_bRunning;
	// 是否最小化
	bool m_bMinimized;
	// 最后一帧的时间
	float m_fLastFrameTime;
	
	// 窗口
	Ref<Window> m_spWindow;
	// 层栈
	Ref<LayerStack> m_spLayerStack;
	// ImGui
	Ref<ImGuiLayer> m_spImGuiLayer;
private:
	// Application指针
	static Ref<Application> m_spApplication;
};

GLCORE_NAMESPACE_END