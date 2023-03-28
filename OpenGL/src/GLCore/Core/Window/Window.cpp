#include "pch.h"

// Windowƽ̨��ʵ�ֵĴ�����
#include "Platform/Windows/WindowsWindow/WindowsWindow.h"

GLCORE_NAMESPACE_BEGIN

// ��������
Ref<Window> Window::Create(const WindowProps& windowPorps)
{
// �����ǰ����ƽ̨��Windows����ʹ��WindowsWindow��������
#ifdef GLCORE_PLATFORM_WINDOWS
	return CreateRef<WindowsWindow>(windowPorps);
#else
	GLCORE_ASSERT(false, "Unkown platform");
	return nullptr;
#endif // GLCORE_PLATFORM_WINDOW
}

// ���캯��
Window::Window(const WindowProps& windowPorps) :
	m_WindowProps(windowPorps)
{
}

GLCORE_NAMESPACE_END