#pragma once

//Do we wnat to include <thread> to increase performance?
//Do later bitch

#include <iostream>
#include <utility>
#include <algorithm>
#include <functional>
#include <future>
#include <Qubit/Core/Log.h>
#include <Qubit/OtherUtility/pair.h>

#include <stdint.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <bitset>
#include <sstream>

#ifdef _WIN32
	#ifdef _WIN64
		#include <windows.h>
	#endif
#endif