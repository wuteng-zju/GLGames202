#pragma once

#include <memory>

// λ����
#define BIT(x) (1<<x)

// ���¼��ص�����
#define BIND_EVENT_FUN(x) std::bind(&x, this, std::placeholders::_1)

// ���������ռ� GLCore
#ifndef GLCORE_NAMESPACE_BEGIN
#define GLCORE_NAMESPACE_BEGIN \
	namespace  GLCore{
#endif 

#ifndef GLCORE_NAMESPACE_END
#define GLCORE_NAMESPACE_END \
	}
#endif 

// ����
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