#pragma once

#include "GLCore/Render/Buffer/VertexBuffer/VertexBuffer.h"
#include "GLCore/Render/Buffer/IndexBuffer/IndexBuffer.h"

GLCORE_NAMESPACE_BEGIN

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;
	void AddVertexBuffer(const Ref<Buffer>& spBuffer);
	const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const;
	void SetIndexBuffer(const Ref<Buffer>& spBuffer);
	const Ref<IndexBuffer>& GetIndexBuffer() const;
	static Ref<VertexArray> Create();
private:
	VertexArray(VertexArray&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;
private:
	unsigned int m_uiRenderID;

	std::vector<Ref<VertexBuffer>> m_vecVertexBuffer;
	Ref<IndexBuffer> m_spIndexBuffer;
};

GLCORE_NAMESPACE_END