#include "pch.h"
#include "TimeStep.h"

#include <GLFW/glfw3.h>

GLCORE_NAMESPACE_BEGIN

// 构造函数
TimeStep::TimeStep(float fTime) :m_fTime(fTime)
{

}

// 以秒为单位获取时间
const float TimeStep::GetSeconds() const
{
	return m_fTime;
}

// 以毫秒为单位获取时间
const float TimeStep::GetMilliSeconds() const
{
	return m_fTime * 1000.f;
}

// 重载()运算符，可以直接获取时间
TimeStep::operator float() const
{
	return m_fTime;
}

// 返回时间
float TimeStep::GetTime()
{
	return glfwGetTime();
}

GLCORE_NAMESPACE_END