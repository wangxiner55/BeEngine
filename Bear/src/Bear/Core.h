#pragma once


#ifdef BR_PLATFORM_WINDOWS
	#ifdef BR_BUILD_DLL
		#define BEAR_API __declspec(dllexport)
	#else 
		#define BEAR_API __declspec(dllimport)
	#endif // BR_BUILD_DLL
#else
#error Hazel only support windows!
#endif // BR_PLATFORM_WINDOWS

#define BIT(x) (1 << x)