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
IncludeDir["GLFW"] = "Nexus/vendor/GLFW/include"
IncludeDir["Glad"] = "Nexus/vendor/Glad/include"
IncludeDir["ImGui"] = "Nexus/vendor/ImGui/include/imgui"
IncludeDir["glm"] = "Nexus/vendor/glm/"

include "Nexus/vendor/GLFW"
include "Nexus/vendor/Glad"
include "Nexus/vendor/ImGui"

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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		defines {
			"NX_PLATFORM_WINDOWS",
			"NX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
		}

	filter "configurations:Debug"
		defines {
			"NX_CONFIG_DEBUG",
			"NX_ENABLE_ASSERTS"
		}
		buildoptions "/MDd"

		symbols "on"

	filter "configurations:Release"
		defines "NX_CONFIG_RELEASE"
		optimize "on"
		buildoptions "/MD"

	filter "configurations:Dist"
		defines "NX_CONFIG_DIST"
		optimize "on"
		buildoptions "/MD"
	
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"Nexus/vendor/spdlog/include",
		"Nexus/src",
		"%{IncludeDir.glm}"
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
		buildoptions "/MDd"

	filter "configurations:Release"
		defines "NX_CONFIG_RELEASE"
		optimize "on"
		buildoptions "/MD"

	filter "configurations:Dist"
		defines "NX_CONFIG_DIST"
		optimize "on"	
		buildoptions "/MD"
