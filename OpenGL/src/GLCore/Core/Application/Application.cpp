#include "pch.h"
#include "Application.h"

GLCORE_NAMESPACE_BEGIN

// 初始化指针
Ref<Application> Application::m_spApplication = nullptr;

// 构造函数
Application::Application(const std::string& name = "GLCore", int width = 1280, int height = 720, int samples = 0) : m_bRunning(true), m_fLastFrameTime(0.f), m_bMinimized(false)
{
	// 创建窗口
	m_spWindow = Window::Create({name, width, height, samples});

	// 设置窗口的事件回调函数为此应用对象的OnEvent函数
	m_spWindow->SetEventCallback(BIND_EVENT_FUN(Application::OnEvent));
}

// 析构函数
Application::~Application()
{

}

// 应用初始化
void Application::Init()
{
	// 创建层栈
	m_spLayerStack = CreateRef<LayerStack>();

	// 创建ImGuiLayer
	m_spImGuiLayer = CreateRef<ImGuiLayer>();

	// 将ImGui作为覆盖层压入层栈
	PushOverlay(m_spImGuiLayer);
}

// 运行应用程序
void Application::Run()
{
	// 渲染循环
	while (m_bRunning)
	{
		// 获取当前时间
		float fTime = TimeStep::GetTime();
		// deltaTime为当前帧与上一帧的时间差
		TimeStep deltaTime = fTime - m_fLastFrameTime;
		// 更新当前帧为上一帧
		m_fLastFrameTime = fTime;

		// 获取当前运行中的应用层栈中的所有layer
		const auto& listLayers = m_spLayerStack->GetLayers();

		// 如果当前窗口没有最小化
		if (!m_bMinimized)
		{
			{
					// 正向遍历层栈，依次调用每一层的更新函数（更新每一层）
					for (auto iter = listLayers.begin(); iter != listLayers.end(); iter++)
					{
						(*iter)->OnUpdate(deltaTime);
					}
			}

			// 统一调用所有层的ImGui函数
			m_spImGuiLayer->BeginNewFrame();
			{
					// 每一个Layer都在调用ImGuiRender函数
					for (auto iter = listLayers.begin(); iter != listLayers.end(); iter++)
					{
						(*iter)->OnImGuiRender();
					}
			}
			m_spImGuiLayer->EndNewFrame();
		}

		// 更新窗口(渲染)
		m_spWindow->OnUpdate();
	}
}

// 
void Application::OnEvent(Event& event)
{
	// 定义事件分发器
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUN(Application::OnMouseButtonPressedEvent));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUN(Application::OnMouseButtonReleasedEvent));
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FUN(Application::OnMouseMovedEvent));
	dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUN(Application::OnMouseScrolledEvent));
	dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUN(Application::OnKeyPressedEvent));
	dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUN(Application::OnKeyReleasedEvent));
	dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FUN(Application::OnKyeTypedEvent));
	dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FUN(Application::OnWindowResizedEvent));
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUN(Application::OnWindowClosedEvent));

	// 反向遍历层栈中的每一层处理事件
	const auto& listLayers = m_spLayerStack->GetLayers();
	for (auto iter = listLayers.rbegin(); iter != listLayers.rend(); iter++)
	{
		if (event.Handle)
		{
			break;
		}
		(*iter)->OnEvent(event);
	}
}

// 
void Application::BlockEvents(bool bBlock)
{
	m_spImGuiLayer->BlockEvents(bBlock);
}

// 
void Application::PushLayer(Ref<Layer> spLayer)
{
	m_spLayerStack->PushLayer(spLayer);
	spLayer->OnAttach();
}

// 
void Application::PushOverlay(Ref<Layer> spLayer)
{
	m_spLayerStack->PushOverlay(spLayer);
	spLayer->OnAttach();
}

// 
void Application::Close()
{
	m_bRunning = false;
}

// 
Ref<Application> Application::GetApplication()
{
	if (m_spApplication == nullptr)
	{
		// 
		m_spApplication = Ref<Application>(new Application());
		// 
		m_spApplication->Init();
	}
	return m_spApplication;
}

// 
bool Application::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
{
	return false;
}

bool Application::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
{
	return false;
}

bool Application::OnMouseMovedEvent(MouseMovedEvent& event)
{
	return false;
}

bool Application::OnMouseScrolledEvent(MouseScrolledEvent& event)
{
	return false;
}

bool Application::OnKeyPressedEvent(KeyPressedEvent& event)
{
	if (event.GetKeyCode() == Key::Escape)
	{
		m_bRunning = false;
	}
	return false;
}

bool Application::OnKeyReleasedEvent(KeyReleasedEvent& event)
{
	return false;
}

bool Application::OnKyeTypedEvent(KeyEvent& event)
{
	return false;
}

bool Application::OnWindowResizedEvent(WindowResizedEvent& event)
{
	if (event.GetWidth() == 0 || event.GetHeight() == 0)
	{
		m_bMinimized = true;
		return false;
	}
	m_bMinimized = false;
	return false;
}

bool Application::OnWindowClosedEvent(WindowCloseEvent& /*event*/)
{
	m_bRunning = false;
	return true;
}

int Application::GetWindowWidth() const
{
	return m_spWindow->GetWindowWidth();
}

int Application::GetWindowHeight() const
{
	return m_spWindow->GetWindowHeight();
}

const Ref<Window>& Application::GetWindow() const
{
	return m_spWindow;
}

GLCORE_NAMESPACE_END


