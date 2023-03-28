#pragma once

// ����
#include "GLcore/Core/Window/Window.h"
// ��ջ
#include "GLCore/Core/Layer/LayerStack/LayerStack.h"
// ImGui
 #include "GLCore/ImGui/ImGuiLayer.h"

GLCORE_NAMESPACE_BEGIN

class Application
{
public:
	// ��ȡApplication
	static Ref<Application> GetApplication();

	static void CreateApplication();

	// ����Application
	void Run();

	// ���캯��
	Application(const std::string& name, int width, int height, int samples);

	// ��������
	virtual ~Application();

	// �ر�Ӧ��
	void Close();

	// �¼����
	void OnEvent(Event& event);
	void BlockEvents(bool bBlock);

	// �������
	int GetWindowWidth() const;
	int GetWindowHeight() const;
	const Ref<Window>& GetWindow()const;

	// Layer���
	void PushLayer(Ref<Layer> spLayer);
	void PushOverlay(Ref<Layer> spLayer);
private:
	// ��ʼ��
	void Init();
	Application(Application&) = delete;
	Application& operator=(const Application&) = delete;
private:
	// a�¼�
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
	// ��ǰApp�Ƿ�������
	bool m_bRunning;
	// �Ƿ���С��
	bool m_bMinimized;
	// ���һ֡��ʱ��
	float m_fLastFrameTime;
	
	// ����
	Ref<Window> m_spWindow;
	// ��ջ
	Ref<LayerStack> m_spLayerStack;
	// ImGui
	Ref<ImGuiLayer> m_spImGuiLayer;
private:
	// Applicationָ��
	static Ref<Application> m_spApplication;
};

GLCORE_NAMESPACE_END