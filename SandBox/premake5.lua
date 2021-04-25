project "SandBox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	defines
    {
        "GLFW_INCLUDE_NONE"
    }

    files
	{
		"src/**.h",
		"src/**.cpp"
	}

    includedirs
	{
		"%{wks.location}/RocketEngine/src",
		"%{wks.location}/RocketEngine/vendor",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
	}

    links
    {
        "RocketEngine"
    }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"