#pragma once

GLCORE_NAMESPACE_BEGIN

// Shader类型：目前-顶点着色器和片元着色器
enum class ShaderType
{
	VETEX_SHADER = 0,
	FRAGMENT_SHADER
};

// 编译类型
enum class CompileType
{
	LINK_STATUS = 0,
	PROGRAM_STATUS
};

// 着色器信息
struct ShaderInfo
{
	// 着色器类型
	ShaderType Type;
	// 着色器名称
	std::string Name;
	// 着色器文件路径
	std::string Path;

	// 构造函数
	ShaderInfo(ShaderType shaderType, const std::string& sPath, const std::string& sName = "")
		: Type(shaderType), Path(sPath), Name(sName)
	{}
};

// 着色器类
class Shader
{
public:
	// 构造函数（一系列的Shader程序，以及一个Shader Program名称）
	Shader(const std::vector<ShaderInfo>& vecShaderInfo, const std::string& sShaderName);
	~Shader();
public:
	// 绑定与解绑
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

	// 获取着色器名称
	const std::string& GetName() const;

	// 创建着色器
	static Ref<Shader> Create(const std::vector<ShaderInfo>& vecShaderInfo, const std::string& sShaderName = "shader");

	// 从文件中读取shader
	std::string ReadFile(const std::string& filepath);

	bool CheckCompileError(unsigned int uiShader, CompileType type);
private:
	Shader(Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
private:
	// Shader Program的id号（program中包含一系列shader）
	unsigned int m_uiRenderID;
	// Shader Program的名称
	std::string m_sShaderName;
};

GLCORE_NAMESPACE_END