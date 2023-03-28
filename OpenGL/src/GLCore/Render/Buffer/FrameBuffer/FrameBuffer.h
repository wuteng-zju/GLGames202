#pragma once

#include "../Buffer.h"

GLCORE_NAMESPACE_BEGIN

enum class FramebufferTextureFormat
{
	None = 0,
	RED_INTERGER,
	RGBA8,
	DEPTH24_STENCIL8,
};

struct FrameBufferTextureSpecification
{
	FramebufferTextureFormat TextureFormat;
	FrameBufferTextureSpecification(FramebufferTextureFormat textureFormat) :
		TextureFormat(textureFormat)
	{

	}
};

struct FrameBufferAttachmentSpecification
{
	std::vector<FrameBufferTextureSpecification> Attachments;
	FrameBufferAttachmentSpecification(std::vector<FrameBufferTextureSpecification> attachments) :
		Attachments(attachments)
	{

	}
};

struct FrameBufferSpecification
{
	Ref<FrameBufferAttachmentSpecification> m_spAttachment;
	unsigned int Width;
	unsigned int Height;
	unsigned int Samples;
	bool SwapChainTarget;
	FrameBufferSpecification(unsigned int uiWidth, unsigned int uiHeight,
		const Ref<FrameBufferAttachmentSpecification>& spAttachment,
		unsigned int uiSamples = 1, bool bSwapChainTarget = false) :
		Width(uiWidth), Height(uiHeight), m_spAttachment(spAttachment), Samples(uiSamples), SwapChainTarget(bSwapChainTarget)
	{

	}
};

// 帧缓冲类（单例模式）
class FrameBuffer :public Buffer
{
public:
	FrameBuffer(const Ref<FrameBufferSpecification>& spFrameBufferSpecification);
	~FrameBuffer();

	virtual void Bind() const override;
	virtual void UnBind() const override;

	static Ref<Buffer> Create(const Ref<FrameBufferSpecification>& spFrameBufferSpecification);
	const Ref<FrameBufferSpecification>& GetFrameBufferSpecification()const;
	virtual void Resize(unsigned int uiWidth, unsigned int uiHeight);
	virtual int ReadPixel(unsigned int uiIndex, unsigned int uiX, unsigned int uiY) const;
	virtual void ClearColorAttachment(unsigned int uiIndex, int iValue) const;

	unsigned int GetColorAttachment(unsigned int uiIndex = 0)const;
	unsigned int GetDepthAttachment()const;
private:
	FrameBuffer() = delete;
	FrameBuffer(FrameBuffer&) = delete;
	FrameBuffer& operator=(const FrameBuffer&) = delete;
private:
	Ref<FrameBufferSpecification> m_spFrameBufferSpecification;
	unsigned int m_uiRenderID;

	std::vector<FrameBufferTextureSpecification> m_vecColorAttachmentSpecifications;
	std::vector<unsigned int> m_vecColorAttachment;

	Ref<FrameBufferTextureSpecification> m_spDepthAttachmentSpecification;
	unsigned int m_uiDepthAttachment;
};

GLCORE_NAMESPACE_END