#include "pch.h"
#include "WindowsWindow.h"

GLCORE_NAMESPACE_BEGIN

// 
namespace
{
	static void GLFWErrorCallback(int error, const char* description)
	{
		LOG_DEV_ERROR("GLFW Error ({0}): {1}", error, description);
	}

}

// ���캯��
WindowsWindow::WindowsWindow(const WindowProps& m_WindowProps) :Window(m_WindowProps)
{
	// ��ʼ������
	Init();
}

// ��������
WindowsWindow::~WindowsWindow()
{
	// ��������
	Shutdown();
}

// ���ڸ���(��Ⱦѭ��)
void WindowsWindow::OnUpdate()
{
	// ����������
	glfwSwapBuffers(m_pGLFWWindow);

	// ��ѯIOʱ�䣨���̻���꣩
	glfwPollEvents();
}

// ��ȡ���ڿ���
inline unsigned int WindowsWindow::GetWindowWidth() const
{
	return m_windowCallBack.Width;
}

// ��ȡ���ڸ߶�
inline unsigned int WindowsWindow::GetWindowHeight() const
{
	return m_windowCallBack.Height;
}

// ���ô����¼��ص�����
inline void WindowsWindow::SetEventCallback(const EventCallbackFn& eventCallBack)
{
	m_windowCallBack.EventCallback = eventCallBack;
}

// ���ô�ֱͬ��
void WindowsWindow::SetVSync(bool bEnabled)
{
	bEnabled ? glfwSwapInterval(1) : glfwSwapInterval(0);
	m_windowCallBack.VSync = bEnabled;
}

// 
bool WindowsWindow::IsVSync() const
{
	return false;
}

// ��ȡԭʼ����
void* WindowsWindow::GetNativeWindow() const
{
	return m_pGLFWWindow;
}

// ���ڳ�ʼ��
void WindowsWindow::Init()
{
	// ��־�����
	LOG_DEV_INFO("Creating window {0} ({1}, {2})",
		m_WindowProps.Title, m_WindowProps.Width, m_WindowProps.Height);

	// ��ʼ��glfw
	bool bGLFWInit = glfwInit();
	GLCORE_ASSERT(bGLFWInit, "Failed to initialize GLFW");

	// ���ô��ڵĿ��ȡ��߶�
	m_windowCallBack.Width = m_WindowProps.Width;
	m_windowCallBack.Height = m_WindowProps.Height;

	// ����OpenGL�汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_WindowProps.MajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_WindowProps.MinorVersion);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// �ж��Ƿ�ʱƻ��ϵͳ
	#ifdef GLCORE_PLATFORM_APPLE
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
		glfwWindowHint(GLFW_SAMPLES, m_WindowProps.Samples);

	// ��������
	{
			m_pGLFWWindow = glfwCreateWindow(m_WindowProps.Width,
				m_WindowProps.Height, m_WindowProps.Title.c_str(), nullptr, nullptr);
	}

	// �жϴ����Ƿ񴴽��ɹ�
	GLCORE_ASSERT(m_pGLFWWindow, "Failed to creat GLFW window");

	// �����ڵ����������óɵ�ǰ�̵߳�������
	glfwMakeContextCurrent(m_pGLFWWindow);

	// ��ʼ����ǰ������
	// ��ʼ��gl3w
	int bInit = gl3wInit();
	GLCORE_ASSERT(!bInit, "Failed to initialize GL3W");

	// ��������С
	LOG_DEV_INFO("{0}", sizeof(float));

	// ͨ��OpenGL��ȡ�豸���Կ���Ϣ
	LOG_DEV_INFO("OpenGL Info:");
	LOG_DEV_INFO("Vendor: {0}", glGetString(GL_VENDOR));	//��ӡ����
	LOG_DEV_INFO("Renderer:{0}", glGetString(GL_RENDERER));
	LOG_DEV_INFO("Version: {0}", glGetString(GL_VERSION));

	/************************** ����GLFW�ص����� *****************************/
	// ����ص�����
	glfwSetErrorCallback(GLFWErrorCallback);

	// �洢m_pGLFWWindow�����Ļص�����ָ��
	glfwSetWindowUserPointer(m_pGLFWWindow, &m_windowCallBack);

	// ������ֱͬ��
	SetVSync(true);

	// ���ڴ�С�ı�Ļص�����
	glfwSetWindowSizeCallback(m_pGLFWWindow, [](GLFWwindow* window, int width, int height)
	{
		// ��ȡm_pGLFWWindow�����Ļص�����ָ��
		auto& pWindowCallBack = *(WindowCallBack*)glfwGetWindowUserPointer(window);
		// ���ô��ڿ��Ⱥ͸߶�
		pWindowCallBack.Width = width;
		pWindowCallBack.Height = height;

		// �����ı䴰�ڵ��¼�
		WindowResizedEvent event(width, height);
		LOG_DEV_WARN("window resize {0},{1}", width, height);

		// ���ô��ڵ��¼��ص�����
		pWindowCallBack.EventCallback(event);
	});

	// ���ڹرյĻص�����
	glfwSetWindowCloseCallback(m_pGLFWWindow, [](GLFWwindow* window)
	{
		auto& pWindowCallBack = *(WindowCallBack*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		pWindowCallBack.EventCallback(event);
	});

	// ���̰����Ļص�����
	glfwSetKeyCallback(m_pGLFWWindow, [](GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
	{
		auto& pWindowCallBack = *(WindowCallBack*)glfwGetWindowUserPointer(window);
		switch (action)
		{
		case GLFW_PRESS:
		{
			KeyPressedEvent event(key, false);
			pWindowCallBack.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent event(key);
			pWindowCallBack.EventCallback(event);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent event(key, true);
			pWindowCallBack.EventCallback(event);
			break;
		}
		}
	});

	// ����ʱ���õ�Event
	glfwSetCharCallback(m_pGLFWWindow, [](GLFWwindow* window, unsigned int keycode)
	{
		auto& pWindowCallBack = *(WindowCallBack*)glfwGetWindowUserPointer(window);

		KeyTypedEvent event(keycode);
		pWindowCallBack.EventCallback(event);
	});

	// ��갴ť�Ļص�����
	glfwSetMouseButtonCallback(m_pGLFWWindow, [](GLFWwindow* window, int button, int action, int mods)
	{
		auto& pWindowCallBack = *(WindowCallBack*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent event(button);
			pWindowCallBack.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent event(button);
			pWindowCallBack.EventCallback(event);
			break;
		}
		}
	});

	// ��껬�ֵĻص�����
	glfwSetScrollCallback(m_pGLFWWindow, [](GLFWwindow* window, double xOffset, double yOffset)
	{
		auto& pWindowCallBack = *(WindowCallBack*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
		pWindowCallBack.EventCallback(event);
	});

	// ���Ļص�����������ƶ���
	glfwSetCursorPosCallback(m_pGLFWWindow, [](GLFWwindow* window, double xPos, double yPos)
	{
		auto& pWindowCallBack = *(WindowCallBack*)glfwGetWindowUserPointer(window);

		MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
		pWindowCallBack.EventCallback(event);
	});
}

// ��������
void WindowsWindow::Shutdown()
{
	glfwDestroyWindow(m_pGLFWWindow);
}
GLCORE_NAMESPACE_END