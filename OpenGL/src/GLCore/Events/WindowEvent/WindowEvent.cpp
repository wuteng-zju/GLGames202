#include "pch.h"
#include "WindowEvent.h"

GLCORE_NAMESPACE_BEGIN

WindowResizedEvent::WindowResizedEvent(unsigned int uiWidth, unsigned int uiHeight) :
	m_uiWidth(uiWidth), m_uiHeight(uiHeight)
{
}

unsigned int WindowResizedEvent::GetWidth() const
{
	return m_uiWidth;
}

unsigned int WindowResizedEvent::GetHeight() const
{
	return m_uiHeight;
}

std::string WindowResizedEvent::ToString() const
{
	std::stringstream ss;
	ss << "WindowResizeEvent: " << m_uiWidth << " , " << m_uiHeight;
	return ss.str();
}

GLCORE_NAMESPACE_END