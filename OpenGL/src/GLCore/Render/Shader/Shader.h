#pragma once

GLCORE_NAMESPACE_BEGIN

// Shader���ͣ�Ŀǰ-������ɫ����ƬԪ��ɫ��
enum class ShaderType
{
	VETEX_SHADER = 0,
	FRAGMENT_SHADER
};

// ��������
enum class CompileType
{
	LINK_STATUS = 0,
	PROGRAM_STATUS
};

// ��ɫ����Ϣ
struct ShaderInfo
{
	// ��ɫ������
	ShaderType Type;
	// ��ɫ������
	std::string Name;
	// ��ɫ���ļ�·��
	std::string Path;

	// ���캯��
	ShaderInfo(ShaderType shaderType, const std::string& sPath, const std::string& sName = "")
		: Type(shaderType), Path(sPath), Name(sName)
	{}
};

// ��ɫ����
class Shader
{
public:
	// ���캯����һϵ�е�Shader�����Լ�һ��Shader Program���ƣ�
	Shader(const std::vector<ShaderInfo>& vecShaderInfo, const std::string& sShaderName);
	~Shader();
public:
	// ������
	void Bind() const;
	void UnBind() const;

	// 
	void SetFloat(const std::string& sName, float fValue);
	void SetFloat2(const std::string& sName, const glm::vec2& vec2Value);
	void SetFloat3(const std::string& sName, const glm::vec3& vec3Value);
	void SetFloat4(const std::string& sName, const glm::vec4& vec4Value);

	void SetMat3(const std::string& name, const glm::mat3& mat3Value);
	void SetMat4(const std::string& sName, const glm::mat4& mat4Value);

	void SetInt(const std::string& sName, int iValue);
	void SetInt2(const std::string& sName, const glm::ivec2& vec2Value);
	void SetInt3(const std::string& sName, const glm::ivec3& vec3Value);
	void SetInt4(const std::string& sName, const glm::ivec4& vec4Value);
	void SetIntArray(const std::string& sName, const int* pValues, unsigned int uiCount);

	void SetBool(const std::string& sName, bool bValue);

	void SetUniformBlock(const std::string& sName, int iBlockBinding);

	// ��ȡ��ɫ������
	const std::string& GetName() const;

	// ������ɫ��
	static Ref<Shader> Create(const std::vector<ShaderInfo>& vecShaderInfo, const std::string& sShaderName = "shader");

	// ���ļ��ж�ȡshader
	std::string ReadFile(const std::string& filepath);

	bool CheckCompileError(unsigned int uiShader, CompileType type);
private:
	Shader(Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
private:
	// Shader Program��id�ţ�program�а���һϵ��shader��
	unsigned int m_uiRenderID;
	// Shader Program������
	std::string m_sShaderName;
};

GLCORE_NAMESPACE_END