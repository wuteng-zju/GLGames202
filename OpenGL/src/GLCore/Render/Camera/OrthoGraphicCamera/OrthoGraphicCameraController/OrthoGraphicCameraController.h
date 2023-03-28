#pragma once

#include "../OrthoGraphicCamera.h"

#include "GLCore/Events/KeyEvent/KeyEvent.h"
#include "GLCore/Events/MouseEvent/MouseEvent.h"
#include "GLCore/Events/ApplicationEvent/ApplicationEvent.h"
#include "GLCore/Events/WindowEvent/WindowEvent.h"

GLCORE_NAMESPACE_BEGIN

struct OrthoGraphicCameraBounds
{
	float Left;
	float Right;
	float Bottom;
	float Top;
	float GetWidth() { return Right - Left; }
	float GetHeight() { return Top - Bottom; }
};

class OrthoGraphicCameraController
{
public:
	OrthoGraphicCameraController(unsigned int uiWidth, unsigned int uiHeight);
	const std::shared_ptr<OrthoGraphicCamera>& GetCamera()const;
	void SetZoomLevel(float fZoomLevel);
	float GetZoomLevel()const;
	void OnUpdate(TimeStep time);
	void OnEvent(Event& event);
	void OnResize(unsigned int uiWidth, unsigned int uiHeight);
	OrthoGraphicCameraBounds GetOrthoGraphicCameraBounds();
private:
	bool OnMouseScrolled(MouseScrolledEvent& e);
	bool OnWindowResized(WindowResizedEvent& e);

private:
	Ref<OrthoGraphicCamera> m_spOrthoGraphicCamera;

	float m_fAspectRatio;
	float m_fZoomLevel;

	float m_fCameraRotation;
	glm::vec3 m_vec3CameraPosition;

	float m_fCameraTranslationSpeed;
	float m_fCameraRotationSpeed;
	float m_fCameraZoomSpeed;

	float m_fTimeStep;
};


GLCORE_NAMESPACE_END
