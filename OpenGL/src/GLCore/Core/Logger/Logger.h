#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

GLCORE_NAMESPACE_BEGIN

// ��־�ࣨ����ģʽ������spdlog��
class Logger
{
public:
	// ��ȡ��־ʵ��
	static Ref<spdlog::logger> GetLogger();
private:
	Logger() = delete;
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
private:
	// ��־ָ��
	static Ref<spdlog::logger> m_spLogger;
};

GLCORE_NAMESPACE_END

// Error
#define LOG_DEV_ERROR(...) ::GLCore::Logger::GetLogger()->error(__VA_ARGS__)
// Warning
#define LOG_DEV_WARN(...) ::GLCore::Logger::GetLogger()->warn(__VA_ARGS__)
// Info
#define LOG_DEV_INFO(...) ::GLCore::Logger::GetLogger()->info(__VA_ARGS__)
// Trace
#define LOG_DEV_TRACE(...) ::GLCore::Logger::GetLogger()->trace(__VA_ARGS__)