#include "pch.h"
#include "OrthoGraphicCameraController.h"

#include "GLCore/Core/Input/Input.h"

GLCORE_NAMESPACE_BEGIN

OrthoGraphicCameraController::OrthoGraphicCameraController(unsigned int uiWidth, unsigned int uiHeight):
	m_fZoomLevel(1.0f),
	m_vec3CameraPosition(glm::vec3(0.f)),
	m_fCameraRotation(0.f),
	m_fCameraTranslationSpeed(5.0f),
	m_fCameraRotationSpeed(180.f),
	m_fCameraZoomSpeed(0.25f),
	m_fTimeStep(0.f)
{
	m_fAspectRatio = static_cast<float>(uiWidth) / static_cast<float>(uiHeight);
	m_spOrthoGraphicCamera = CreateRef<OrthoGraphicCamera>(m_fZoomLevel, m_fAspectRatio);
}

const std::shared_ptr<OrthoGraphicCamera>& OrthoGraphicCameraController::GetCamera() const
{
	return m_spOrthoGraphicCamera;
}

void OrthoGraphicCameraController::SetZoomLevel(float fZoomLevel)
{
	m_fZoomLevel = fZoomLevel;
	m_spOrthoGraphicCamera->SetOrthoSize(m_fZoomLevel);
}

float OrthoGraphicCameraController::GetZoomLevel() const
{
	return m_fZoomLevel;
}

void OrthoGraphicCameraController::OnUpdate(TimeStep timeStep)
{
	if (Input::IsKeyPressed(Key::W))
	{
		m_vec3CameraPosition.y += m_fCameraTranslationSpeed * timeStep;
	}
	else if (Input::IsKeyPressed(Key::S))
	{
		m_vec3CameraPosition.y -= m_fCameraTranslationSpeed * timeStep;
	}

	if (Input::IsKeyPressed(Key::A))
	{
		m_vec3CameraPosition.x -= m_fCameraTranslationSpeed * timeStep;
	}
	else if (Input::IsKeyPressed(Key::D))
	{
		m_vec3CameraPosition.x += m_fCameraTranslationSpeed * timeStep;
	}

	if (Input::IsKeyPressed(Key::Q))
	{
		m_fCameraRotation -= m_fCameraRotationSpeed * timeStep;
	}
	else if (Input::IsKeyPressed(Key::E))
	{
		m_fCameraRotation += m_fCameraRotationSpeed * timeStep;
	}

	auto cameraRotation = glm::quat(glm::vec3(0.f, 0.f, m_fCameraRotation));
	m_spOrthoGraphicCamera->SetRotation(cameraRotation);
	m_spOrthoGraphicCamera->SetPosition(m_vec3CameraPosition);
}

void OrthoGraphicCameraController::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUN(OrthoGraphicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FUN(OrthoGraphicCameraController::OnWindowResized));
}

void OrthoGraphicCameraController::OnResize(unsigned int uiWidth, unsigned int uiHeight)
{
	m_spOrthoGraphicCamera->SetViewPortSize(uiWidth, uiHeight);
}

OrthoGraphicCameraBounds OrthoGraphicCameraController::GetOrthoGraphicCameraBounds()
{
	OrthoGraphicCameraBounds orthoGraphicCameraBounds;
	orthoGraphicCameraBounds.Left = -m_fAspectRatio * m_fZoomLevel;
	orthoGraphicCameraBounds.Right = m_fAspectRatio * m_fZoomLevel;
	orthoGraphicCameraBounds.Bottom = -m_fZoomLevel;
	orthoGraphicCameraBounds.Top = m_fZoomLevel;
	return orthoGraphicCameraBounds;
}

bool OrthoGraphicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	m_fZoomLevel -= e.GetYOffset() * m_fCameraZoomSpeed;
	m_fZoomLevel = std::max(m_fZoomLevel, m_fCameraZoomSpeed);
	m_spOrthoGraphicCamera->SetOrthoSize(m_fZoomLevel);
	return false;
}

bool OrthoGraphicCameraController::OnWindowResized(WindowResizedEvent& e)
{
	OnResize(e.GetWidth(), e.GetHeight());
	return false;
}

GLCORE_NAMESPACE_END


