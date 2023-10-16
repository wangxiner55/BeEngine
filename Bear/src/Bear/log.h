#pragma once
#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"


namespace BEngine {


	class BEAR_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

#define BR_CORE_ERROR(...) ::BEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BR_CORE_WARN(...)  ::BEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BR_CORE_INFO(...)  ::BEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BR_CORE_TRACE(...) ::BEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BR_CORE_FATAL(...) ::BEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define BR_CLIENT_ERROR(...) ::BEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define BR_CLIENT_WARN(...)  ::BEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BR_CLIENT_INFO(...)  ::BEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define BR_CLIENT_TRACE(...) ::BEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BR_CLIENT_FATAL(...) ::BEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)
}