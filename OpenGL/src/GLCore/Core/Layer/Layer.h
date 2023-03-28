#pragma once
#include "pch.h"
#include "GLCore/Events/Event.h"

GLCORE_NAMESPACE_BEGIN

// �������
class Layer
{
public:
	// ���캯��
	Layer(const std::string& sLayerName = "Layer") :m_sLayerName(sLayerName) {}
	// ��������
	virtual ~Layer() {};
	// ���㱻�����ջ��ʱ�����ӣ����൱��Layer�ĳ�ʼ����
	virtual void OnAttach() {};
	// ���㱻�Ƴ���ջ��ʱ�򣨷��룩���൱��Layer�����٣�
	virtual void OnDetach() {};
	// ���㱻���µ�ʱ�����ڴ�����Ⱦ��loop��
	virtual void OnUpdate(const TimeStep&) {};
	// �����¼�
	virtual void OnEvent(Event&) {};
	// ����ImGui�Ľӿ�
	virtual void OnImGuiRender() {}
	// ��ȡ����
	const std::string& GetName()const { return m_sLayerName; }
protected:
	// �������
	std::string m_sLayerName;
};

GLCORE_NAMESPACE_END