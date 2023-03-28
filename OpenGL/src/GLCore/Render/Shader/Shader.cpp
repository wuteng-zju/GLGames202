#include "pch.h"
#include "Shader.h"

#define GL_GLEXT_PROTOTYPES
#include "GL/gl3w.h"

GLCORE_NAMESPACE_BEGIN

// 获取着色器的Shader类型
namespace
{
	GLenum GetShaderType(ShaderType shaderType)
	{
		switch (shaderType)
		{
		case GLCore::ShaderType::VETEX_SHADER: return GL_VERTEX_SHADER;
		case GLCore::ShaderType::FRAGMENT_SHADER: return GL_FRAGMENT_SHADER;
		default:
		{
			GLCORE_ASSERT(false, "Unknonw Shader Type");
			return 0;
		}
		}
	}
}

Ref<Shader> Shader::Create(const std::vector<ShaderInfo>& vecShaderInfo, const std::string& sShaderName)
{
	return Ref<Shader>(new Shader(vecShaderInfo, sShaderName));
}

Shader::Shader(const std::vector<ShaderInfo>& vecShaderInfo, const std::string& sShaderName): 
	m_sShaderName(sShaderName)
{
	// 创建Program
	GLuint uiProgram = glCreateProgram();

	// 着色器ids
	std::vector<GLuint> vecShaderIDs;
	vecShaderIDs.reserve(vecShaderInfo.size());

	// 遍历所有的着色器
	for (auto& shaderInfo : vecShaderInfo)
	{
		// 创建当前着色器
		GLuint uiShader = glCreateShader(GetShaderType(shaderInfo.Type));
		// 加入ids
		vecShaderIDs.emplace_back(uiShader);
		// 读取着色器源码
		auto pSource = ReadFile(shaderInfo.Path);
		const char* pSourceCode = pSource.c_str();
		GLCORE_ASSERT(pSourceCode, "Shader Source in OpenGLShader is null");
		glShaderSource(uiShader, 1, &pSourceCode, NULL);

		// 编译着色器代码
		glCompileShader(uiShader);

		// 处理编译出错
		if (!CheckCompileError(uiShader, CompileType::LINK_STATUS))
		{
			for (auto& shader : vecShaderIDs)
			{
				glDeleteShader(shader);
			}
			GLCORE_ASSERT(false, "Shader Compile Failed");
		}

		// 将当前编译成功的着色器附加到Program中
		glAttachShader(uiProgram, uiShader);
	}

	// 链接
	glLinkProgram(uiProgram);

	// 处理链接出错
	if (!CheckCompileError(uiProgram, CompileType::PROGRAM_STATUS))
	{
		for (auto& shader : vecShaderIDs)
		{
			glDeleteShader(shader);
		}
		GLCORE_ASSERT(false, "Program Compile Failed");
	}

	// 链接成功后删除着色器
	for (auto& shader : vecShaderIDs)
	{
		glDeleteShader(shader);
	}

	// program id
	m_uiRenderID = uiProgram;
}

Shader::~Shader()
{
	glDeleteProgram(m_uiRenderID);
}

bool Shader::CheckCompileError(unsigned int uiShader, CompileType compileType)
{
	switch (compileType)
	{
	case GLCore::CompileType::LINK_STATUS:
	{
		GLint iComplied(-1);
		glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iComplied);
		if (!iComplied)
		{
			GLsizei uiLen(0);
			glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &uiLen);

			std::vector<GLchar> vecLogInfo(uiLen);
			glGetShaderInfoLog(uiShader, uiLen, &uiLen, &vecLogInfo[0]);
			LOG_DEV_ERROR(vecLogInfo.data());
			return false;
		}
		return true;
	}
	case GLCore::CompileType::PROGRAM_STATUS:
	{
		GLint iComplied(-1);
		glGetShaderiv(uiShader, GL_LINK_STATUS, &iComplied);
		if (!iComplied)
		{
			GLsizei uiLen(0);
			glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &uiLen);

			std::vector<GLchar> vecLogInfo(uiLen);
			glGetShaderInfoLog(uiShader, uiLen, &uiLen, &vecLogInfo[0]);
			LOG_DEV_ERROR(vecLogInfo.data());
			return false;
		}
		return true;
	}
	default:
	{
		GLCORE_ASSERT(false, "Unknow Complie Tye");
		return false;
	}
	}
}

void Shader::Bind() const
{
	glUseProgram(m_uiRenderID);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

std::string Shader::ReadFile(const std::string& sFilepath)
{
	std::ifstream ifSteam(sFilepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
	if (ifSteam)
	{
		ifSteam.seekg(0, std::ios::end);
		size_t stSize = ifSteam.tellg();
		if (stSize != -1)
		{
			std::string sResult("");
			sResult.resize(stSize);
			ifSteam.seekg(0, std::ios::beg);
			ifSteam.read(&sResult[0], stSize);
			return sResult;
		}
		else
		{
			LOG_DEV_ERROR("Could not read from file '{0}'", sFilepath);
		}
	}
	else
	{
		LOG_DEV_ERROR("Could not open file '{0}'", sFilepath);
	}
	return "";
}

/*****************************************  *******************************************/
void Shader::SetFloat(const std::string& sName, float fValue)
{
	GLint iLocation = glGetUniformLocation(m_uiRenderID, sName.c_str());
	glUniform1f(iLocation, fValue);
}

void Shader::SetFloat2(const std::string& sName, const glm::vec2& vec2Value)
{
	GLint iLocation = glGetUniformLocation(m_uiRenderID, sName.c_str());
	glUniform2fv(iLocation, 1, &vec2Value[0]);
}

void Shader::SetFloat3(const std::string& sName, const glm::vec3& vec3Value)
{
	GLint iLocation = glGetUniformLocation(m_uiRenderID, sName.c_str());
	glUniform3fv(iLocation, 1, &vec3Value[0]);
}

void Shader::SetFloat4(const std::string& sName, const glm::vec4& vec4Value)
{
	GLint iLocation = glGetUniformLocation(m_uiRenderID, sName.c_str());
	glUniform4fv(iLocation, 1, &vec4Value[0]);
}

void Shader::SetMat3(const std::string& sName, const glm::mat3& mat3Value)
{
	GLint iLocation = glGetUniformLocation(m_uiRenderID, sName.c_str());
	glUniformMatrix3fv(iLocation, 1, GL_FALSE, &mat3Value[0][0]);
}

void Shader::SetMat4(const std::string& sName, const glm::mat4& mat4Value)
{
	GLint iLocation = glGetUniformLocation(m_uiRenderID, sName.c_str());
	glUniformMatrix4fv(iLocation, 1, GL_FALSE, &mat4Value[0][0]);
}

void Shader::SetInt(const std::string& sName, int iValue)
{
	GLint iLocation = glGetUniformLocation(m_uiRenderID, sName.c_str());
	glUniform1i(iLocation, iValue);
}

void Shader::SetInt2(const std::string& sName, const glm::ivec2& vec2Value)
{
	GLint iLocation = glGetUniformLocation(m_uiRenderID, sName.c_str());
	glUniform2iv(iLocation, 1, &vec2Value[0]);
}

void Shader::SetInt3(const std::string& sName, const glm::ivec3& vec3Value)
{
	GLint iLocation = glGetUniformLocation(m_uiRenderID, sName.c_str());
	glUniform3iv(iLocation, 1, &vec3Value[0]);
}

void Shader::SetInt4(const std::string& sName, const glm::ivec4& vec4Value)
{
	GLint iLocation = glGetUniformLocation(m_uiRenderID, sName.c_str());
	glUniform4iv(iLocation, 1, &vec4Value[0]);
}

void Shader::SetIntArray(const std::string& sName, const int* pValues, unsigned int uiCount)
{
	GLint iLocation = glGetUniformLocation(m_uiRenderID, sName.c_str());
	glUniform1iv(iLocation, uiCount, pValues);
}

void Shader::SetBool(const std::string& sName, bool bValue)
{
	GLint iLocation = glGetUniformLocation(m_uiRenderID, sName.c_str());
	glUniform1i(iLocation, bValue);
}

void Shader::SetUniformBlock(const std::string& sName, int iBlockBinding)
{
	auto uiBlockIndex = glGetUniformBlockIndex(m_uiRenderID, sName.c_str());
	glUniformBlockBinding(m_uiRenderID, uiBlockIndex, iBlockBinding);
}

const std::string& Shader::GetName() const
{
	return m_sShaderName;
}

GLCORE_NAMESPACE_END


