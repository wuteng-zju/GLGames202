#include "pch.h"
#include "IndexBuffer.h"

#define GL_GLEXT_PROTOTYPES
#include "GL/gl3w.h"

GLCORE_NAMESPACE_BEGIN

Ref<Buffer> IndexBuffer::Create(const std::vector<unsigned int>& vecIndex)
{
	return CreateRef<IndexBuffer>(vecIndex);
}

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& vecIndex) :
	m_vecIndex(vecIndex),
	m_uiRenderID(0)
{
	glGenBuffers(1, &m_uiRenderID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiRenderID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vecIndex.size() * sizeof(unsigned int), vecIndex.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_uiRenderID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiRenderID);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

const std::vector<unsigned int> IndexBuffer::GetIndex() const
{
	return m_vecIndex;
}

GLCORE_NAMESPACE_END