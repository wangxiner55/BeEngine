#pragma once
#include <memory>

#ifndef CORE_COMP
#define CORE_COMP



#ifdef BR_PLATFORM_WINDOWS
#if BR_DYNAMIC_LINK
	#ifdef BR_BUILD_DLL
		#define BEAR_API __declspec(dllexport)
	#else 
		#define BEAR_API __declspec(dllimport)
	#endif // BR_BUILD_DLL
#else
	#define BEAR_API
#endif
#else
#error Hazel only support windows!
#endif // BR_PLATFORM_WINDOWS

#ifdef HZ_ENABLE_ASSERTS
#define BR_ASSERT(x,...){if(!(x)){BR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#define BR_CORE_ASSERT(x,...){if(!(x)){BR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}

#else
#define BR_ASSERT(x,...)
#define BR_CORE_ASSERT(x,...)

#endif // HZ_ENABLE_ASSERTS


#define BIT(x) (1 << x)



#define EVENT_BIND(x) std::bind(&x, this, std::placeholders::_1)




namespace BEngine
{
	template<typename T>
	using Uniq = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;





}



#endif // !CORE_COMP