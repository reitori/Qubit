#pragma once
//Definitions for logger class

//Include some other logger API later

/* Logger class:
*	- For logging/debugging purposes
*	-
*	-
*/
namespace Qubit {

	__declspec(dllexport) void test(const char* message);

	class __declspec(dllexport) Logger {
	public:
		Logger() = default;
		inline static void CoreLog(const char* message);
		inline static void ClientLog(const char* message);

		~Logger() = default;
	private:
		static const Logger* s_Logger;
	};
}