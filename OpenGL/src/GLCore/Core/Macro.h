#pragma once

#include <memory>

// 位运算
#define BIT(x) (1<<x)

// 绑定事件回调函数
#define BIND_EVENT_FUN(x) std::bind(&x, this, std::placeholders::_1)

// 定义命名空间 GLCore
#ifndef GLCORE_NAMESPACE_BEGIN
#define GLCORE_NAMESPACE_BEGIN \
	namespace  GLCore{
#endif 

#ifndef GLCORE_NAMESPACE_END
#define GLCORE_NAMESPACE_END \
	}
#endif 

// 断言
#ifdef GLCORE_ENABLE_ASSERTS
#define GLCORE_ASSERT(x,...) { if(!(x)) { LOG_DEV_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}

#endif // GLCORE_ENABLE_ASSERTS


GLCORE_NAMESPACE_BEGIN

// Scope = unique_ptr
template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

// Ref = shared_ptr
template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

GLCORE_NAMESPACE_END