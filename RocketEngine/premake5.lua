project "RocketEngine"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    defines
    {
        "GLFW_INCLUDE_NONE"
    }

    links
    {
        "vendor/GLFWold/lib-x86_64/glfw3",
        "Glad",
        "OpenGL.framework",
        "Cocoa.framework",
        "IOKit.framework"
    }

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp",
        "RocketEngine/src/**.h",
        "RocketEngine/src/**.cpp",
        "RocketEngine/vendor/**.h",
        "RocketEngine/vendor/**.cpp",
        "vendor/stb_image/**.h",
        "vendor/stb_image/**.cpp",
        "vendor/glm/**.hpp",
        "vendor/glm/**.inl"
    }

    includedirs
    {
        "src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLEW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
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