#pragma once

#if defined(NX_PLATFORM_WINDOWS)
	#if defined(NX_BUILD_DLL)
		#define NEXUS_API __declspec(dllexport)
	#else
		#define NEXUS_API __declspec(dllimport)
	#endif
#else
	#error Nexus only supports Windows
#endif