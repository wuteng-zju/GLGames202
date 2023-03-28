#include "pch.h"
#include "WindowsInput.h"

#include "GLFW/glfw3.h"

#include "GLCore/Core/Application/Application.h"

GLCORE_NAMESPACE_BEGIN

Ref<Input> Input::m_spInput = Ref<WindowsInput>(new WindowsInput());

bool WindowsInput::IsKeyPressedImpl(KeyCode keyCode)
{
	// ��ȡ��ǰӦ�õĴ���
	const auto& spWindow = Application::GetApplication()->GetWindow();
	GLCORE_ASSERT(spWindow, "WindowsInput get window failed");
	// ��ȡ��Ӧ��glfw����
	auto glfwWindow = static_cast<GLFWwindow*>(spWindow->GetNativeWindow());
	GLCORE_ASSERT(glfwWindow, "WindowsInput get glfwWindow failed");

	// ����GLFW�Ķ�Ӧ�����жϼ����Ƿ���
	auto state = glfwGetKey(glfwWindow, keyCode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::IsMouseButtonPressedImpl(MouseCode mouseCode)
{
	const auto& upWindow = Application::GetApplication()->GetWindow();
	GLCORE_ASSERT(upWindow, "WindowsInput get window failed");
	auto glfwWindow = static_cast<GLFWwindow*>(upWindow->GetNativeWindow());
	GLCORE_ASSERT(glfwWindow, "WindowsInput get glfwWindow failed");

	auto state = glfwGetMouseButton(glfwWindow, mouseCode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

glm::vec2 WindowsInput::GetMousePosImpl()
{
	const auto& upWindow = Application::GetApplication()->GetWindow();
	GLCORE_ASSERT(upWindow, "WindowsInput get window failed");
	auto glfwWindow = static_cast<GLFWwindow*>(upWindow->GetNativeWindow());
	GLCORE_ASSERT(glfwWindow, "WindowsInput get glfwWindow failed");

	double dXPos(0.0), dYPos(0.0);
	glfwGetCursorPos(glfwWindow, &dXPos, &dYPos);
	return glm::vec2(dXPos, dYPos);
}

float WindowsInput::GetMouseXPosImpl()
{
	auto vec2Pos = GetMousePosImpl();
	return vec2Pos.x;
}

float WindowsInput::GetMouseYPosImpl()
{
	auto vec2Pos = GetMousePosImpl();
	return vec2Pos.y;
}

GLCORE_NAMESPACE_END