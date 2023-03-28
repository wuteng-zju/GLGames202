#pragma once

#include "GLCore/Core/Layer/Layer.h"

GLCORE_NAMESPACE_BEGIN

class ImGuiLayer :public Layer
{
public:
	// 构造函数
	ImGuiLayer();
	// 析构函数
	~ImGuiLayer();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(Event&) override;
	// 开始新的一帧
	void BeginNewFrame();
	// 结束新的一帧
	void EndNewFrame();
	// 阻塞事件
	void BlockEvents(bool bBlock);
private:
	// 是否阻塞事件
	bool m_bBlockEvents;
};

GLCORE_NAMESPACE_END