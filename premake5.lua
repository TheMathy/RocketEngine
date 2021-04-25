workspace "RocketEngine"
    architecture "x86_64"
    startproject "RocketEngine"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    flags
    {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/RocketEngine/vendor/GLFW/include"
IncludeDir["GLEW"] = "%{wks.location}/RocketEngine/vendor/GLEW/include"
IncludeDir["Glad"] = "%{wks.location}/RocketEngine/vendor/Glad/include"
IncludeDir["glm"] = "%{wks.location}/RocketEngine/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/RocketEngine/vendor/stb_image"

group "Dependencies"
	include "RocketEngine/vendor/GLFW"
	include "RocketEngine/vendor/Glad"
group ""

include "RocketEngine"
include "SandBox"