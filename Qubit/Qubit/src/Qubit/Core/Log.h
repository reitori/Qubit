#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Qubit {
	class QBT_API Log {
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_CoreLogger; }
		
		static void printError(const char* message, std::shared_ptr<spdlog::logger>& logger);
		static void printInfo(const char* message, std::shared_ptr<spdlog::logger>& logger);
		static void printWarning(const char* message, std::shared_ptr<spdlog::logger>& logger);
	};
}

#define GBLN_CORE_TRACE(...)			::Goblin::Log::getCoreLogger->trace(__VA_ARGS__)
#define GBLN_CORE_WARN(...)				::Goblin::Log::getCoreLogger->warn(__VA_ARGS__)
#define GBLN_CORE_ERROR(...)			::Goblin::Log::getCoreLogger->error(__VA_ARGS__)
#define GBLN_CORE_INFO(...)				::Goblin::Log::getCoreLogger->info(__VA_ARGS__)
#define GBLN_CORE_FATAL(...)			::Goblin::Log::getCoreLogger->fatal(__VA_ARGS__)


#define GBLN_CLIENT_TRACE(...)			::Goblin::Log::getClientLogger->trace(__VA_ARGS__)
#define GBLN_CLIENT_WARN(...)			::Goblin::Log::getClientLogger->warn(__VA_ARGS__)
#define GBLN_CLIENT_ERROR(...)			::Goblin::Log::getClientLogger->error(__VA_ARGS__)
#define GBLN_CLIENT_INFO(...)			::Goblin::Log::getClientLogger->info(__VA_ARGS__)
#define GBLN_CLIENT_FATAL(...)			::Goblin::Log::getClientLogger->fatal(__VA_ARGS__)