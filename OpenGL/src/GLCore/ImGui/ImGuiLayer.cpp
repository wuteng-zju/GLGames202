#include "pch.h"
#include "ImGuiLayer.h"

#include "GLFW/glfw3.h"

#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "GLCore/Core/Application/Application.h"


GLCORE_NAMESPACE_BEGIN

// 构造函数
ImGuiLayer::ImGuiLayer() :Layer("ImguiLayer"), m_bBlockEvents(true)
{

}

// 析构函数
ImGuiLayer::~ImGuiLayer()
{
	LOG_DEV_INFO("ImGuiLayer Finalize");
}

// 压入层栈时
void ImGuiLayer::OnAttach()
{
	// 创建ImGui上下文
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); 
	(void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	//float fontSize = 18.0f;// *2.0f;

	//// 字体设置
	//io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", fontSize);
	//io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", fontSize);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	//// Setup Platform/Renderer bindings
	const auto& upWindow = Application::GetApplication()->GetWindow();
	GLCORE_ASSERT(upWindow, "ImGuiLayer get window failed");
	auto glfwWindow = static_cast<GLFWwindow*>(upWindow->GetNativeWindow());
	GLCORE_ASSERT(glfwWindow, "ImGuiLayer get glfwWindow failed");

	//// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiLayer::OnEvent(Event& e)
{
	e.Handle = m_bBlockEvents;
}

// 开始新的一帧
void ImGuiLayer::BeginNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiLayer::EndNewFrame()
{
	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void ImGuiLayer::BlockEvents(bool bBlock)
{
	m_bBlockEvents = bBlock;
}


GLCORE_NAMESPACE_END