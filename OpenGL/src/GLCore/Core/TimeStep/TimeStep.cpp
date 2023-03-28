#include "pch.h"
#include "TimeStep.h"

#include <GLFW/glfw3.h>

GLCORE_NAMESPACE_BEGIN

// ���캯��
TimeStep::TimeStep(float fTime) :m_fTime(fTime)
{

}

// ����Ϊ��λ��ȡʱ��
const float TimeStep::GetSeconds() const
{
	return m_fTime;
}

// �Ժ���Ϊ��λ��ȡʱ��
const float TimeStep::GetMilliSeconds() const
{
	return m_fTime * 1000.f;
}

// ����()�����������ֱ�ӻ�ȡʱ��
TimeStep::operator float() const
{
	return m_fTime;
}

// ����ʱ��
float TimeStep::GetTime()
{
	return glfwGetTime();
}

GLCORE_NAMESPACE_END