#pragma once

GLCORE_NAMESPACE_BEGIN

// 顶点数据类型
enum class VertexDataType
{
	None = 0,
	Float, Float2, Float3, Float4,
	Mat3, Mat4,
	Int, Int2, Int3, Int4,
	Bool
};

// 顶点缓冲元素
struct VertexBufferElement
{
	// 顶点缓冲名称
	std::string Name;
	// 顶点数据类型
	VertexDataType DataType;
	// 是否归一化
	bool Normalized;
	// 大小
	int Size;
	// 偏移量
	int Offset;

	// 构造函数
	VertexBufferElement(VertexDataType dataType, const std::string& sName = "", bool bNormalized = false) :
		DataType(dataType), Name(sName), Size(VertexDataTypeSize(dataType)), Offset(0), Normalized(bNormalized)
	{}

	int GetDataCount() const
	{
		switch (DataType)
		{
			case VertexDataType::Float:		return 1;
			case VertexDataType::Float2:	return 2;
			case VertexDataType::Float3:	return 3;
			case VertexDataType::Float4:	return 4;
			case VertexDataType::Mat3:		return 3 * 3;
			case VertexDataType::Mat4:		return 4 * 4;
			case VertexDataType::Int:		return 1;
			case VertexDataType::Int2:		return 2;
			case VertexDataType::Int3:		return 3;
			case VertexDataType::Int4:		return 4;
			case VertexDataType::Bool:		return 1;
			default:
			{
				GLCORE_ASSERT(false, "Unknown DataType");
				return 0;
			}
		}
	}

	int VertexDataTypeSize(VertexDataType vertexDataType)
	{
		switch (vertexDataType)
		{
			case VertexDataType::None:		return 0;
			case VertexDataType::Float:		return 1 * sizeof(float);
			case VertexDataType::Float2:	return 2 * sizeof(float);
			case VertexDataType::Float3:	return 3 * sizeof(float);
			case VertexDataType::Float4:	return 4 * sizeof(float);
			case VertexDataType::Mat3:		return 3 * 3 * sizeof(float);
			case VertexDataType::Mat4:		return 4 * 4 * sizeof(float);
			case VertexDataType::Int:		return 1 * sizeof(int);
			case VertexDataType::Int2:		return 2 * sizeof(int);
			case VertexDataType::Int3:		return 3 * sizeof(int);
			case VertexDataType::Int4:		return 4 * sizeof(int);
			case VertexDataType::Bool:		return 1 * sizeof(bool);
			default:
			{
				GLCORE_ASSERT(false, "Unknown DataType");
				return 0;
			}
		}
	}
};

// 顶点缓冲布局VAO
class VertexBufferLayout
{
public:
	// 析构函数
	~VertexBufferLayout() = default;
	// 构造函数
	VertexBufferLayout(const std::vector<VertexBufferElement>& vecVertexBufferElement);
	// 
	const std::vector<VertexBufferElement>& GetVertexBufferElements()const;
	int GetStride()const;

private:
	// 一个顶点缓冲数组
	std::vector<VertexBufferElement> m_vecVertexBufferElement;
	// 步长
	int m_iStride;
};

GLCORE_NAMESPACE_END