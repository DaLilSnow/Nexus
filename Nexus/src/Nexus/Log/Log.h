#pragma once
#include "nxpch.h"
#include <spdlog\spdlog.h>
#include "Nexus/Core.h"
#include <spdlog/fmt/ostr.h>
	
namespace Nexus {

	class NEXUS_API Log {
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#if defined(NX_CONFIG_DEBUG)
	#define NX_CORE_TRACE(...) ::Nexus::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define NX_CORE_INFO(...)  ::Nexus::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define NX_CORE_WARN(...)  ::Nexus::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define NX_CORE_ERROR(...) ::Nexus::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define NX_CORE_FATAL(...) ::Nexus::Log::GetCoreLogger()->fatal(__VA_ARGS__)

	#define NX_TRACE(...)      ::Nexus::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define NX_INFO(...)       ::Nexus::Log::GetClientLogger()->info(__VA_ARGS__)
	#define NX_WARN(...)       ::Nexus::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define NX_ERROR(...)      ::Nexus::Log::GetClientLogger()->error(__VA_ARGS__)
	#define NX_FATAL(...)      ::Nexus::Log::GetClientLogger()->fatal(__VA_ARGS__)
#else

#define NX_CORE_TRACE(x)
#define NX_CORE_INFO(x)
#define NX_CORE_WARN(x)
#define NX_CORE_ERROR(x)

#define NX_TRACE(x)
#define NX_INFO(x)
#define NX_WARN(x)
#define NX_ERROR(x)

#endif