#include "log.h"


namespace BEngine {
	Ref<spdlog::logger> LogSystem::s_CoreLogger;
	Ref<spdlog::logger> LogSystem::s_ClientLogger;


	void LogSystem::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("BEAR");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}