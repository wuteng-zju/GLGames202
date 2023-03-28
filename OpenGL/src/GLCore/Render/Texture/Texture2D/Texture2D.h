#pragma once

#include "../Texture.h"

GLCORE_NAMESPACE_BEGIN

class Texture2D : public Texture
{
public:
	Texture2D(const std::string& sPath);
	Texture2D(int iWidth, int iHeight);

	~Texture2D();

	// Í¨¹ý Texture ¼Ì³Ð
	int GetWidth() const override;
	int GetHeight() const override;

	static Ref<Texture> Create(const std::string& sPath);
	static Ref<Texture> Create(unsigned int uiWidth, unsigned int uiHeight);

	unsigned int GetRenderID() const override;
	const std::string& GetTexturePath()const;

	void Bind(unsigned int uiPos = 0) const override;
	void SetData(void* pData, unsigned int uiSize) override;
	void UnBind()const override;
private:
	Texture2D() = delete;
	Texture2D(Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;
protected:
	std::string m_sPath;
	int m_iWidth;
	int m_iHeight;
	int m_iChannel;

	unsigned int m_uiRenderID;
	unsigned int m_uiInternalFormat;
	unsigned int m_uiDataFormat;
};

GLCORE_NAMESPACE_END