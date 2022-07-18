workspace "Nexus"
	architecture "x64"
	configurations { 
		"Debug", 
		"Release",
		"Dist"
	}
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Nexus/vendor/glfw/include"

include "Nexus/vendor/glfw"

project "Nexus"
	location "Nexus"
	kind "SharedLib"
	language "C++"

	targetdir ( "bin/" .. outputdir .. "/%{prj.name}" )
	objdir ( "bin-int/" .. outputdir .. "/%{prj.name}" )

	pchheader "nxpch.h"
	pchsource "Nexus/src/nxpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links {
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		defines {
			"NX_PLATFORM_WINDOWS",
			"NX_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
		}

	filter "configurations:Debug"
		defines {
			"NX_CONFIG_DEBUG",
			"NX_ENABLE_ASSERTS"
		}

		symbols "on"

	filter "configurations:Release"
		defines "NX_CONFIG_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "NX_CONFIG_DIST"
		optimize "on"
	
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"Nexus/vendor/spdlog/include",
		"Nexus/src"
	}

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	links "Nexus" 

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		defines {
			"NX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines {
			"NX_CONFIG_DEBUG",
			"NX_ENABLE_ASSERTS"
		}
		symbols "on"

	filter "configurations:Release"
		defines "NX_CONFIG_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "NX_CONFIG_DIST"
		optimize "on"	