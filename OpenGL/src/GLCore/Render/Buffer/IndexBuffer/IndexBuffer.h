#pragma once

#include "../Buffer.h"

GLCORE_NAMESPACE_BEGIN

// Ë÷Òý»º³åÀà
class IndexBuffer :public Buffer
{
public:
	IndexBuffer(const std::vector<unsigned int>& vecIndex);
	~IndexBuffer();

	void Bind() const override;
	void UnBind() const override;

	static Ref<Buffer> Create(const std::vector<unsigned int>& vecIndex);
	const std::vector<unsigned int> GetIndex()const;
private:
	IndexBuffer() = delete;
	IndexBuffer(IndexBuffer&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;
private:
	unsigned int m_uiRenderID;
	std::vector<unsigned int> m_vecIndex;
};

GLCORE_NAMESPACE_END