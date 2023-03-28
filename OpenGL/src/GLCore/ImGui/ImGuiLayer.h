#pragma once

#include "GLCore/Core/Layer/Layer.h"

GLCORE_NAMESPACE_BEGIN

class ImGuiLayer :public Layer
{
public:
	// ���캯��
	ImGuiLayer();
	// ��������
	~ImGuiLayer();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(Event&) override;
	// ��ʼ�µ�һ֡
	void BeginNewFrame();
	// �����µ�һ֡
	void EndNewFrame();
	// �����¼�
	void BlockEvents(bool bBlock);
private:
	// �Ƿ������¼�
	bool m_bBlockEvents;
};

GLCORE_NAMESPACE_END