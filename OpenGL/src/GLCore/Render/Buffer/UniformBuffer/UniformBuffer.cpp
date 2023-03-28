#include "pch.h"
#include "UniformBuffer.h"

#define GL_GLEXT_PROTOTYPES
#include "GL/gl3w.h"

GLCORE_NAMESPACE_BEGIN

Ref<Buffer> UniformBuffer::Create(unsigned int uiSize, unsigned int uiBinding)
{
	return CreateRef<UniformBuffer>(uiSize, uiBinding);
}

UniformBuffer::UniformBuffer(unsigned int uiSize, unsigned int uiBinding)
{
	glGenBuffers(1, &m_uiRenderID);

	glBindBuffer(GL_UNIFORM_BUFFER, m_uiRenderID);
	glBufferData(GL_UNIFORM_BUFFER, uiSize, NULL, GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, uiBinding, m_uiRenderID, 0, uiSize);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &m_uiRenderID);
}

void UniformBuffer::SetData(const void* data, unsigned int uiSize, unsigned int uiOffset)
{
	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, uiOffset, uiSize, data);
	UnBind();
}

void UniformBuffer::Bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_uiRenderID);
}

void UniformBuffer::UnBind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLCORE_NAMESPACE_END