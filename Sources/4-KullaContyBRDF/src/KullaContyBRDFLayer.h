#pragma once
#include <GLCore.h>
#include <imgui/imgui.h>

using namespace GLCore;

class ShadowMapLayer : public Layer
{
public:
	ShadowMapLayer();
	virtual ~ShadowMapLayer();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(const TimeStep& timeStep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Event& e) override;
private:
	// Па»ъ
	Ref<OrthoGraphicCameraController> m_spOrthoGraphicCameraController;

	Ref<VertexArray> m_spColorArray;
	Ref<Shader> m_spColorShader;
	glm::vec4 m_vec4Color;
};