#pragma once
#include <glm/gtc/matrix_transform.hpp>

GLCORE_NAMESPACE_BEGIN

// 投影类型：透视投影或正交投影
enum class ProjectionType
{
	Perspective = 0,
	Orthographic
};


const std::array<std::string, 2> ProjectionTypeStrings = { "Perspective","Orthographic" };


struct CameraMatrix
{
	glm::mat4 ViewProjection;
};

// 相机抽象类
class Camera
{
public:
	Camera(float fAspectRatio, float fNear, float fFar, ProjectionType eProjectionType);
	~Camera() = default;
	void SetPosition(const glm::vec3& vec3Position);
	const glm::vec3& GetPositon()const;
	void SetScale(const glm::vec3& vec3Scale);
	const glm::vec3& GetScale()const;
	void SetRotation(const glm::quat& quatRotation);
	const glm::quat& GetRotaion()const;

	void SetProjectionMatrix(const glm::mat4& mat4ProjectionMatrix);
	const glm::mat4& GetProjectionMatrix()const;
	void SetViewMatrix(const glm::mat4& mat4ViewMatrix);
	const glm::mat4& GetViewMatrix()const;
	const glm::mat4& GetViewProjectionMatrix()const;
	ProjectionType GetProjectionType();
	void SetProjectionType(ProjectionType eProjectionType);

	void SetNearAndFarClip(float fNear, float fFar);
	void SetNearClip(float fNear);
	float GetNearClip() const;
	void SetFarClip(float fFar);
	float GetFarClip() const;

	void SetViewPortSize(unsigned int uiWidth, unsigned int uiHeight);
	void SetAspectRatio(float fAspectRatio);
	float GetAspectRatio();
protected:
	virtual void RecalculateProjectionMatrix() = 0;
	void RecalculateViewProjectionMatrix();
	void RecalculateViewMatrix();
protected:
	// 相机投影类型
	ProjectionType m_eProjectionType;
	// 投影矩阵
	glm::mat4 m_mat4ProjectionMatrix;
	// 视点矩阵
	glm::mat4 m_mat4ViewMatrix;
	// VP矩阵
	glm::mat4 m_mat4ViewProjectionMatrix;

	// 相机位置
	glm::vec3 m_vec3Position;
	// 缩放
	glm::vec3 m_vec3Scale;
	// 旋转
	glm::quat m_quatRotation;

	// 近裁剪平面
	float m_fNearClip;
	// 远裁剪平面
	float m_fFarClip;
	// 宽高比
	float m_fAspectRatio;
	// 视口宽度、高度
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;
};

GLCORE_NAMESPACE_END
