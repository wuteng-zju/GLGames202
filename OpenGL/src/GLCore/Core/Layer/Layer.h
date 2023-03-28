#pragma once
#include "pch.h"
#include "GLCore/Events/Event.h"

GLCORE_NAMESPACE_BEGIN

// 层抽象类
class Layer
{
public:
	// 构造函数
	Layer(const std::string& sLayerName = "Layer") :m_sLayerName(sLayerName) {}
	// 析构函数
	virtual ~Layer() {};
	// 当层被推入层栈的时候（链接）（相当于Layer的初始化）
	virtual void OnAttach() {};
	// 当层被移除层栈的时候（分离）（相当于Layer的销毁）
	virtual void OnDetach() {};
	// 当层被更新的时候（用于处理渲染的loop）
	virtual void OnUpdate(const TimeStep&) {};
	// 处理事件
	virtual void OnEvent(Event&) {};
	// 绘制ImGui的接口
	virtual void OnImGuiRender() {}
	// 获取层名
	const std::string& GetName()const { return m_sLayerName; }
protected:
	// 层的名称
	std::string m_sLayerName;
};

GLCORE_NAMESPACE_END