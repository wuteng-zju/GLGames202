#pragma once

#include "pch.h"

GLCORE_NAMESPACE_BEGIN

// �������
class Buffer
{
public:
	// ʹ��Ĭ����������
	virtual ~Buffer() = default;
	// ��
	virtual void Bind() const = 0;
	// ���
	virtual void UnBind() const = 0;
};

GLCORE_NAMESPACE_END