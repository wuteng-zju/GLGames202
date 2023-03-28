#pragma once

#include "pch.h"

GLCORE_NAMESPACE_BEGIN

// 缓冲基类
class Buffer
{
public:
	// 使用默认析构函数
	virtual ~Buffer() = default;
	// 绑定
	virtual void Bind() const = 0;
	// 解绑
	virtual void UnBind() const = 0;
};

GLCORE_NAMESPACE_END