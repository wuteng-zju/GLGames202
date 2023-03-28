#pragma once

GLCORE_NAMESPACE_BEGIN

// 时间类
class TimeStep
{
public:
	// 构造函数
	TimeStep(float fTime = 0.f);
	// 以秒为单位获取时间
	const float GetSeconds() const;
	// 以毫秒为单位获取时间
	const float GetMilliSeconds()const;
	// 函数对象
	operator float()const;
	// 获取时间
	static float GetTime();
private:
	// 时间值
	float m_fTime;
};

GLCORE_NAMESPACE_END