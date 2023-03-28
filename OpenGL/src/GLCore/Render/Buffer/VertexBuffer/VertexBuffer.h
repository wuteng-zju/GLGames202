#pragma once

#include "../Buffer.h"
#include "VertexBufferLayout/VertexBufferLayout.h"

GLCORE_NAMESPACE_BEGIN

// 顶点缓冲类
class VertexBuffer :public Buffer
{
public:
	VertexBuffer(const std::vector<float>& vecVertics, const Ref<VertexBufferLayout>& spVertexBufferLayout);
	VertexBuffer(const std::vector<float>& vecVertics);
	VertexBuffer(unsigned int uiVertexSize);

	// 析构函数
	~VertexBuffer();

	void SetVertexBufferLayout(const Ref<VertexBufferLayout>& spVertexBufferLayout);
	const Ref<VertexBufferLayout>& GetVertexBufferLayout()const;
	const std::vector<float>& GetVertex()const;

	void SetData(const void* pData, uint32_t uiVertexSize);

	virtual void Bind() const override;
	virtual void UnBind() const override;

	static Ref<Buffer> Create(const std::vector<float>& vecVertex, const Ref<VertexBufferLayout>& spVertexBufferLayout);
	static Ref<Buffer> Create(const std::vector<float>& vecVertex);
	static Ref<Buffer> Create(unsigned int uiVertexSize);
private:
	VertexBuffer(VertexBuffer&) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;
private:
	unsigned int m_uiRenderID;
	std::vector<float> m_vecVertex;
	// 顶点数据布局
	Ref<VertexBufferLayout> m_spVertexBufferLayout;
};

GLCORE_NAMESPACE_END