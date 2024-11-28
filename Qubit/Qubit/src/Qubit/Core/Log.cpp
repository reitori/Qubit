#include <QubitPCH.h>

#include "Log.h"

namespace Qubit {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%D: %R - %n]: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("QUBIT");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("CLIENT");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	void Log::printError(const char* message, std::shared_ptr<spdlog::logger>& logger) {
		spdlog::set_pattern("%^[[ERR]%D: %R - %n]: %v%$");
		logger->error(message);
	}

	void Log::printInfo(const char* message, std::shared_ptr<spdlog::logger>& logger) {
		spdlog::set_pattern("%^[[INF]%D: %R - %n]: %v%$");
		logger->info(message);
	}

	void Log::printWarning(const char* message, std::shared_ptr<spdlog::logger>& logger) {
		spdlog::set_pattern("%^[[WRN]%D: %R - %n]: %v%$");
		logger->warn(message);
	}
}