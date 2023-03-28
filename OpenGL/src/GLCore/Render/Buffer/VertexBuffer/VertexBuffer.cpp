#include "pch.h"
#include "VertexBuffer.h"

#define GL_GLEXT_PROTOTYPES
#include "GL/gl3w.h"

GLCORE_NAMESPACE_BEGIN

Ref<Buffer> VertexBuffer::Create(const std::vector<float>& vecVertex, const Ref<VertexBufferLayout>& spVertexBufferLayout)
{
	return CreateRef<VertexBuffer>(vecVertex, spVertexBufferLayout);;
}

Ref<Buffer> VertexBuffer::Create(const std::vector<float>& vecVertex)
{
	return CreateRef<VertexBuffer>(vecVertex);;
}

Ref<Buffer> VertexBuffer::Create(unsigned int uiVertexSize)
{
	return CreateRef<VertexBuffer>(uiVertexSize);;
}

VertexBuffer::VertexBuffer(const std::vector<float>& vecVertics,
	const Ref<VertexBufferLayout>& spVertexBufferLayout) :
	m_vecVertex(vecVertics),
	m_spVertexBufferLayout(spVertexBufferLayout)
{
	glGenBuffers(1, &m_uiRenderID);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiRenderID);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size(), m_vecVertex.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::VertexBuffer(const std::vector<float>& vecVertics) :
	m_vecVertex(vecVertics),
	m_spVertexBufferLayout(nullptr)
{
	glGenBuffers(1, &m_uiRenderID);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiRenderID);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size(), m_vecVertex.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::VertexBuffer(unsigned int uiVertexSize)
{
	glCreateBuffers(1, &m_uiRenderID);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiRenderID);
	glBufferData(GL_ARRAY_BUFFER, uiVertexSize, nullptr, GL_DYNAMIC_DRAW);
}

void VertexBuffer::SetData(const void* pData, uint32_t uiVertexSize)
{
	GLCORE_ASSERT(pData, "SetData is Null in OpenGLVertexBuffer");
	glBindBuffer(GL_ARRAY_BUFFER, m_uiRenderID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, uiVertexSize, pData);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_uiRenderID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_uiRenderID);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const std::vector<float>& VertexBuffer::GetVertex() const
{
	return m_vecVertex;
}

const Ref<VertexBufferLayout>& VertexBuffer::GetVertexBufferLayout() const
{
	return m_spVertexBufferLayout;
}

void VertexBuffer::SetVertexBufferLayout(const Ref<VertexBufferLayout>& spVertexBufferLayout)
{
	m_spVertexBufferLayout = spVertexBufferLayout;
}

GLCORE_NAMESPACE_END