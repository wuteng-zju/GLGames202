#include "pch.h"
#include "VertexArray.h"

#define GL_GLEXT_PROTOTYPES
#include "GL/gl3w.h"

GLCORE_NAMESPACE_BEGIN

Ref<VertexArray> VertexArray::Create()
{
	return CreateRef<VertexArray>();
}

GLenum GetDataType(VertexDataType dataType)
{
	switch (dataType)
	{
	case VertexDataType::Float:		return GL_FLOAT;
	case VertexDataType::Float2:		return GL_FLOAT;
	case VertexDataType::Float3:		return GL_FLOAT;
	case VertexDataType::Float4:		return GL_FLOAT;
	case VertexDataType::Mat3:		return GL_FLOAT;
	case VertexDataType::Mat4:		return GL_FLOAT;
	case VertexDataType::Int:			return GL_INT;
	case VertexDataType::Int2:		return GL_INT;
	case VertexDataType::Int3:		return GL_INT;
	case VertexDataType::Int4:		return GL_INT;
	case VertexDataType::Bool:		return GL_BOOL;
	default:
	{
		GLCORE_ASSERT(false, "Unknown DataType");
		return 0;
	}
	}
}

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_uiRenderID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_uiRenderID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_uiRenderID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const Ref<Buffer>& spBuffer)
{
	auto spVertexBuffer = std::dynamic_pointer_cast<VertexBuffer>(spBuffer);
	GLCORE_ASSERT(spVertexBuffer, "Vertex Buffer in OpenGLVertexArray is null");

	const auto& spVertexBufferLayout = spVertexBuffer->GetVertexBufferLayout();
	GLCORE_ASSERT(spVertexBufferLayout->GetVertexBufferElements().size(), "Vertex Buffer has no layout");

	glBindVertexArray(m_uiRenderID);
	spVertexBuffer->Bind();

	GLuint uiIndex(0);
	for (const auto& element : spVertexBufferLayout->GetVertexBufferElements())
	{
		glEnableVertexAttribArray(uiIndex);
		glVertexAttribPointer(
			uiIndex,
			element.GetDataCount(),
			GetDataType(element.DataType),
			element.Normalized ? GL_TRUE : GL_FALSE,
			spVertexBufferLayout->GetStride(),
			(const void*)(element.Offset));
		uiIndex++;
	}

	spVertexBuffer->UnBind();
	glBindVertexArray(0);
	m_vecVertexBuffer.push_back(spVertexBuffer);
}

const std::vector<Ref<VertexBuffer>>& VertexArray::GetVertexBuffer() const
{
	return m_vecVertexBuffer;
}

void VertexArray::SetIndexBuffer(const Ref<Buffer>& spBuffer)
{
	m_spIndexBuffer = std::dynamic_pointer_cast<IndexBuffer>(spBuffer);
	GLCORE_ASSERT(m_spIndexBuffer, "Vertex Buffer in OpenGLVertexArray is null");

	Bind();
	m_spIndexBuffer->Bind();
}

const Ref<IndexBuffer>& VertexArray::GetIndexBuffer() const
{
	return m_spIndexBuffer;
}

GLCORE_NAMESPACE_END