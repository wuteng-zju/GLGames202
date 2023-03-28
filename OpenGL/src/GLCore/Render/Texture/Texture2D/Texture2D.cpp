#include "pch.h"
#include "Texture2D.h"

#include "GL/gl3w.h"
#include "stb_image.h"

GLCORE_NAMESPACE_BEGIN

namespace
{
	void GetFormat(int iChannels, GLenum& uiInternalFormat, GLenum& uiDataFormat)
	{
		switch (iChannels)
		{
		case 1:
		{
			uiInternalFormat = GL_RED;
			uiDataFormat = GL_RED;
			break;
		}
		case 3:
		{
			uiInternalFormat = GL_RGB8;
			uiDataFormat = GL_RGB;
			break;
		}
		case 4:
		{
			uiInternalFormat = GL_RGBA8;
			uiDataFormat = GL_RGBA;
			break;
		}
		default:
		{
			LOG_DEV_ERROR("Unkown Image Data Channel");
			break;
		}
		}
	}

}

Texture2D::Texture2D(int iWidth, int iHeight) :
	m_uiInternalFormat(GL_RGBA8), 
	m_uiDataFormat(GL_RGBA), 
	m_sPath(""),
	m_iWidth(iWidth),
	m_iHeight(iHeight),
	m_iChannel(0),
	m_uiRenderID(0)
{
	glGenTextures(1, &m_uiRenderID);
	glBindTexture(GL_TEXTURE_2D, m_uiRenderID);
	glTextureStorage2D(m_uiRenderID, 1, m_uiInternalFormat, m_iWidth, m_iHeight);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::Texture2D(const std::string& sPath) :
	m_sPath(sPath),
	m_iWidth(0),
	m_iHeight(0),
	m_iChannel(0),
	m_uiRenderID(0)
{
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* pImageData = nullptr;
	{
		pImageData = stbi_load(m_sPath.c_str(), &m_iWidth, &m_iHeight, &m_iChannel, 0);
	}

	GLCORE_ASSERT(pImageData, "Image Load in OpenGLTexture2D Failed");

	GetFormat(m_iChannel, m_uiInternalFormat, m_uiDataFormat);

	glGenTextures(1, &m_uiRenderID);
	glBindTexture(GL_TEXTURE_2D, m_uiRenderID);
	glTexImage2D(GL_TEXTURE_2D, 0, m_uiInternalFormat, m_iWidth, m_iHeight, 0,
		m_uiDataFormat, GL_UNSIGNED_BYTE, pImageData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(pImageData);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_uiRenderID);
}

int Texture2D::GetWidth() const
{
	return m_iWidth;
}

int Texture2D::GetHeight() const
{
	return m_iHeight;
}

Ref<Texture> Texture2D::Create(const std::string& sPath)
{
	return CreateRef<Texture2D>(sPath);
}

Ref<Texture> Texture2D::Create(unsigned int uiWidth, unsigned int uiHeight)
{
	return CreateRef<Texture2D>(uiWidth, uiHeight);
}

unsigned int Texture2D::GetRenderID() const
{
	return m_uiRenderID;
}

const std::string& Texture2D::GetTexturePath() const
{
	return m_sPath;
}

void Texture2D::Bind(unsigned int uiPos) const
{
	glActiveTexture(GL_TEXTURE0 + uiPos);
	glBindTexture(GL_TEXTURE_2D, m_uiRenderID);
}

void Texture2D::SetData(void* pData, unsigned int uiSize)
{
	int iChannel = m_uiDataFormat == GL_RGBA ? 4 : 3;
	GLCORE_ASSERT(uiSize = m_iWidth * m_iHeight * iChannel, "Data must be entire in OpenGLTexture2D");
	GLCORE_ASSERT(pData, "Data is null in OpenGLTexture2D");
	glTextureSubImage2D(m_uiRenderID, 0, 0, 0, m_iWidth, m_iHeight, m_uiDataFormat, GL_UNSIGNED_BYTE, pData);
}

void Texture2D::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLCORE_NAMESPACE_END