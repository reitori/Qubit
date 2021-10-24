#include <qbtpch.h>
#include "Logger.h"

namespace Qubit {
	//Defines the Logger Singleton
	const Logger* Logger::s_Logger = new Logger;

	inline void Logger::CoreLog(const char* message) {
		std::cout << "CORE: " << message << std::endl;
	}

	inline void Logger::ClientLog(const char* message) {
		std::cout << "CLIENT: " << message << std::endl;
	}



	__declspec(dllexport) void test(const char* message) {
		std::cout << "You said: " << message << std::endl;
	}
}