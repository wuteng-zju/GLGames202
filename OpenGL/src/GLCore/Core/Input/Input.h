#pragma once
#include "Code/KeyCode.h"
#include "Code/MouseCode.h"

GLCORE_NAMESPACE_BEGIN

// 输入类（单例模式）
class Input
{
public:
	// 键盘是否按下
	static bool IsKeyPressed(KeyCode keyCode);

	// 鼠标是否点击
	static bool IsMouseButtonPressed(KeyCode keyCode);

	// 获取鼠标位置、X坐标、Y坐标
	static glm::vec2 GetMousePos();
	static float GetMouseXPos();
	static float GetMouseYPos();

	// 析构函数
	~Input() = default;
protected:
	virtual bool IsKeyPressedImpl(KeyCode keyCode) = 0;
	virtual bool IsMouseButtonPressedImpl(MouseCode mouseCode) = 0;
	virtual glm::vec2 GetMousePosImpl() = 0;
	virtual float GetMouseXPosImpl() = 0;
	virtual float GetMouseYPosImpl() = 0;

protected:
	Input() = default;
private:
	Input(Input&) = delete;
	Input& operator=(const Input&) = delete;

private:
	// 
	static Ref<Input> m_spInput;
};

GLCORE_NAMESPACE_END