#pragma once
#include "../Base/Core.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"


namespace BEngine {


	class BEAR_API LogSystem
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:

		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;

	};

#define BR_CORE_ERROR(...) ::BEngine::LogSystem::GetCoreLogger()->error(__VA_ARGS__)
#define BR_CORE_WARN(...)  ::BEngine::LogSystem::GetCoreLogger()->warn(__VA_ARGS__)
#define BR_CORE_INFO(...)  ::BEngine::LogSystem::GetCoreLogger()->info(__VA_ARGS__)
#define BR_CORE_TRACE(...) ::BEngine::LogSystem::GetCoreLogger()->trace(__VA_ARGS__)
#define BR_CORE_FATAL(...) ::BEngine::LogSystem::GetCoreLogger()->fatal(__VA_ARGS__)

#define BR_CLIENT_ERROR(...) ::BEngine::LogSystem::GetClientLogger()->error(__VA_ARGS__)
#define BR_CLIENT_WARN(...)  ::BEngine::LogSystem::GetClientLogger()->warn(__VA_ARGS__)
#define BR_CLIENT_INFO(...)  ::BEngine::LogSystem::GetClientLogger()->info(__VA_ARGS__)
#define BR_CLIENT_TRACE(...) ::BEngine::LogSystem::GetClientLogger()->trace(__VA_ARGS__)
#define BR_CLIENT_FATAL(...) ::BEngine::LogSystem::GetClientLogger()->fatal(__VA_ARGS__)
}