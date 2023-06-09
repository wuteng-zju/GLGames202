#include "pch.h"
#include "VertexBufferLayout.h"

GLCORE_NAMESPACE_BEGIN

VertexBufferLayout::VertexBufferLayout(const std::vector<VertexBufferElement>& vecVertexBufferElement) :
	m_vecVertexBufferElement(vecVertexBufferElement), m_iStride(0)
{
	int iOffset(0);
	for (auto& element : m_vecVertexBufferElement)
	{
		element.Offset = iOffset;
		iOffset += element.Size;
		m_iStride += element.Size;
	}
}

int VertexBufferLayout::GetStride() const
{
	return m_iStride;
}

const std::vector<VertexBufferElement>& VertexBufferLayout::GetVertexBufferElements() const
{
	return m_vecVertexBufferElement;
}

GLCORE_NAMESPACE_END