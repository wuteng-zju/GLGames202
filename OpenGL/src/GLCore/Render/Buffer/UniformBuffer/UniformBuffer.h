#pragma once

#include "../Buffer.h"

GLCORE_NAMESPACE_BEGIN

// 全局变量缓冲类
class UniformBuffer :public Buffer
{
public:
	UniformBuffer(unsigned int uiSize, unsigned int uiBinding);
	~UniformBuffer();

	static Ref<Buffer> Create(unsigned int uiSize, unsigned int uiBinding);

	void SetData(const void* data, unsigned int uiSize, unsigned int uiOffset = 0);

	void Bind() const override;
	void UnBind() const override;
private:
	UniformBuffer(UniformBuffer&) = delete;
	UniformBuffer& operator=(const UniformBuffer&) = delete;
private:
	unsigned int m_uiRenderID;
};

GLCORE_NAMESPACE_END