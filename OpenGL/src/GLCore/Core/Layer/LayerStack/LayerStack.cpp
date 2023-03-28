#include "pch.h"
#include "LayerStack.h"

GLCORE_NAMESPACE_BEGIN

// 析构函数
LayerStack::~LayerStack()
{
	m_listLayers.clear();
}

// 把层推入层栈（插到列表的前面）
void LayerStack::PushLayer(Ref<Layer> spLayer)
{
	m_listLayers.emplace_front(spLayer);
}

// 把覆盖层推入层栈（插到列表的尾端）
void LayerStack::PushOverlay(Ref<Layer> spLayer)
{
	m_listLayers.emplace_back(spLayer);
}

// 从层栈中推出一个层（尾部）
void LayerStack::PopLayer(Ref<Layer> spLayer)
{
	m_listLayers.pop_back();
}

// 从层栈中推出覆盖层（尾部）
void LayerStack::PopOverlay(Ref<Layer> spLayer)
{
	m_listLayers.pop_back();
}

const std::list<Ref<Layer>>& LayerStack::GetLayers() const
{
	return m_listLayers;
}

GLCORE_NAMESPACE_END