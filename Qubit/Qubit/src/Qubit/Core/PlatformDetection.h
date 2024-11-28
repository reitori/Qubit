//Do the other stuff later
#pragma once
#ifdef _WIN32
	#ifdef _WIN64
		#define GBLN_PLATFORM_WINDOWS
	
	#else
		#error Qubit does not support x86 builds.
	#endif // DEBUG
#endif // _WIN32
