#pragma once

	#ifdef QBT_BUILD_DLL
		#define QBT_API __declspec(dllexport)
	#else
		#define QBT_API __declspec(dllimport)
	#endif