#pragma once

// �¼�
#include "GLCore/Events/KeyEvent/KeyEvent.h"
#include "GLCore/Events/MouseEvent/MouseEvent.h"
#include "GLCore/Events/ApplicationEvent/ApplicationEvent.h"
#include "GLCore/Events/WindowEvent/WindowEvent.h"

GLCORE_NAMESPACE_BEGIN

// ��������
struct WindowProps
{
	// ���ڱ���
	std::string Title;

	// ���ڿ�Ⱥ͸߶�
	int Width;
	int Height;

	// OpenGL�汾��
	int MajorVersion;
	int MinorVersion;

	// ���ز��������ڿ���ݣ�
	int Samples;

	// ���캯��
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

// �¼��ص�����
using EventCallbackFn = std::function<void(Event&)>;

// ���ڳ����࣬����ģʽ
class Window
{
public:
	// �����������麯����
	virtual ~Window() {}

	// ÿһ֡����
	virtual void OnUpdate() = 0;

	/********************** �������� ************************/
	// ��ȡ���ڿ�ȣ����麯����
	virtual unsigned int GetWindowWidth() const = 0;
	// ��ȡ���ڸ߶ȣ����麯����
	virtual unsigned int GetWindowHeight() const = 0;
	// ���ô����¼��ص�����,ƽ̨����
	virtual void SetEventCallback(const EventCallbackFn& callback) = 0; 
	// ���ô�ֱͬ��
	virtual void SetVSync(bool enabled) = 0;
	// �Ƿ�����ֱͬ��
	virtual bool IsVSync() const = 0;
	// ��ȡԭʼ����
	virtual void* GetNativeWindow()const = 0;

	/********************** �������� ************************/
	static Ref<Window> Create(const WindowProps& windowPorps = WindowProps());
protected:
	// ���캯��
	Window(const WindowProps& windowPorps);
private:
	// ɾ��Ĭ�Ϲ��졢��������Ϳ�����ֵ����������ڵ���ģʽ��
	Window() = delete;
	Window(Window&) = delete;
	Window& operator=(const Window&) = delete;
protected:
	// ��������
	WindowProps m_WindowProps;
};

GLCORE_NAMESPACE_END