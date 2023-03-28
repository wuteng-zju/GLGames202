#pragma once

GLCORE_NAMESPACE_BEGIN

// ʱ����
class TimeStep
{
public:
	// ���캯��
	TimeStep(float fTime = 0.f);
	// ����Ϊ��λ��ȡʱ��
	const float GetSeconds() const;
	// �Ժ���Ϊ��λ��ȡʱ��
	const float GetMilliSeconds()const;
	// ��������
	operator float()const;
	// ��ȡʱ��
	static float GetTime();
private:
	// ʱ��ֵ
	float m_fTime;
};

GLCORE_NAMESPACE_END