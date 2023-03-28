#include "pch.h"
#include "Render.h"

#include "GL/gl3w.h"

GLCORE_NAMESPACE_BEGIN

void Render::Init()
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
}

void Render::SetClearColor(const glm::vec4& vec4Color)
{
	glClearColor(vec4Color.r, vec4Color.g, vec4Color.b, vec4Color.a);
}

void Render::SetViewPort(unsigned int uiWidth, unsigned int uiHeight)
{
	glViewport(0, 0, uiWidth, uiHeight);
}

void Render::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Render::DrawTriangles(unsigned int uiIndexCount)
{
	glDrawElements(GL_TRIANGLES, uiIndexCount, GL_UNSIGNED_INT, nullptr);
}

void Render::DrawLines(unsigned int uiIndexCount)
{
	glDrawArrays(GL_LINES, 0, uiIndexCount);
}

void Render::SetLineWidth(float fWidth)
{
	glLineWidth(fWidth);
}

GLCORE_NAMESPACE_END


