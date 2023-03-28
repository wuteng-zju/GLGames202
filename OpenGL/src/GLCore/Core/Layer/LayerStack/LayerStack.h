#pragma once

#include "GLCore/Core/Layer/Layer.h"

GLCORE_NAMESPACE_BEGIN

// 层栈类
class LayerStack
{
public:
	// 构造函数
	LayerStack() = default;
	// 析构函数
	~LayerStack();

	/********************* 层 ***********************/
	// 把层推入层栈
	void PushLayer(Ref<Layer> spLayer);
	// 从层栈中推出一个层
	void PopLayer(Ref<Layer> spLayer);

	/********************* 覆盖层 ***********************/
	// 向层栈中推入覆盖层
	void PushOverlay(Ref<Layer> spLayer);
	// 从层栈中推出覆盖层
	void PopOverlay(Ref<Layer> spLayer);
	// 获取层栈中的所有层
	const std::list<Ref<Layer>>& GetLayers()const;
private:
	// 层栈中的所有层组成的列表
	std::list<Ref<Layer>> m_listLayers;
};

GLCORE_NAMESPACE_END