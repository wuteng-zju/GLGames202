#pragma once
#include "GLCore/Core/Input/Input.h"

GLCORE_NAMESPACE_BEGIN

// Windowsƽ̨�µ�Input������
class WindowsInput :public Input
{
protected:
	virtual bool IsKeyPressedImpl(KeyCode keyCode) override;
	virtual bool IsMouseButtonPressedImpl(MouseCode mouseCode)override;
	virtual glm::vec2 GetMousePosImpl()override;
	virtual float GetMouseXPosImpl() override;
	virtual float GetMouseYPosImpl() override;
};

GLCORE_NAMESPACE_END