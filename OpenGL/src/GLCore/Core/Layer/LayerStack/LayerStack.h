#pragma once

#include "GLCore/Core/Layer/Layer.h"

GLCORE_NAMESPACE_BEGIN

// ��ջ��
class LayerStack
{
public:
	// ���캯��
	LayerStack() = default;
	// ��������
	~LayerStack();

	/********************* �� ***********************/
	// �Ѳ������ջ
	void PushLayer(Ref<Layer> spLayer);
	// �Ӳ�ջ���Ƴ�һ����
	void PopLayer(Ref<Layer> spLayer);

	/********************* ���ǲ� ***********************/
	// ���ջ�����븲�ǲ�
	void PushOverlay(Ref<Layer> spLayer);
	// �Ӳ�ջ���Ƴ����ǲ�
	void PopOverlay(Ref<Layer> spLayer);
	// ��ȡ��ջ�е����в�
	const std::list<Ref<Layer>>& GetLayers()const;
private:
	// ��ջ�е����в���ɵ��б�
	std::list<Ref<Layer>> m_listLayers;
};

GLCORE_NAMESPACE_END