#pragma once

#include "../Camera.h"

GLCORE_NAMESPACE_BEGIN

// 透视相机类
class PerspectiveGraphicCamera :public Camera
{
public:
	PerspectiveGraphicCamera();
	PerspectiveGraphicCamera(float fFOV, float fAspectRatio, float fNearClip = 0.1f, float fFarClip = 1000.f);
	void SetPerspectiveFOV(float fFOV);
	float GetPerspectiveFOV();
private:
	void RecalculateProjectionMatrix() override;
private:
	float m_fFOV;
};

GLCORE_NAMESPACE_END

