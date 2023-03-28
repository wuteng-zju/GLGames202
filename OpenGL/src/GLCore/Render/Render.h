#pragma once

GLCORE_NAMESPACE_BEGIN

class Render
{
public:
	static void Init();
	static void SetClearColor(const glm::vec4& vec4Color);
	static void SetViewPort(unsigned int uiWidth, unsigned int uiHeight);
	static void Clear();
	static void DrawTriangles(unsigned int uiIndexCount);
	static void DrawLines(unsigned int uiIndexCount);
	static void SetLineWidth(float fWidth);
};

GLCORE_NAMESPACE_END