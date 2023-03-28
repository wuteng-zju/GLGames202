#include "pch.h"
#include "LayerStack.h"

GLCORE_NAMESPACE_BEGIN

// ��������
LayerStack::~LayerStack()
{
	m_listLayers.clear();
}

// �Ѳ������ջ���嵽�б���ǰ�棩
void LayerStack::PushLayer(Ref<Layer> spLayer)
{
	m_listLayers.emplace_front(spLayer);
}

// �Ѹ��ǲ������ջ���嵽�б���β�ˣ�
void LayerStack::PushOverlay(Ref<Layer> spLayer)
{
	m_listLayers.emplace_back(spLayer);
}

// �Ӳ�ջ���Ƴ�һ���㣨β����
void LayerStack::PopLayer(Ref<Layer> spLayer)
{
	m_listLayers.pop_back();
}

// �Ӳ�ջ���Ƴ����ǲ㣨β����
void LayerStack::PopOverlay(Ref<Layer> spLayer)
{
	m_listLayers.pop_back();
}

const std::list<Ref<Layer>>& LayerStack::GetLayers() const
{
	return m_listLayers;
}

GLCORE_NAMESPACE_END