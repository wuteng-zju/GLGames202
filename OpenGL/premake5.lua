-- project OpenGL
project "OpenGL"
	-- 项目类型：静态库
	kind "StaticLib"

	-- 语言：C++
	language "C++"

	-- C++标准 
	cppdialect "C++17"

	-- 
	staticruntime "on"

	-- 指定输出目录
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

	-- 指定中间目录
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	-- 预编译头文件
	pchheader "pch.h"

	-- vs需要包含
	pchsource "src/pch.cpp"

  
	files
	{
		-- 加载src目录下的所有.h,.cpp文件
		"src/**.h",
		"src/**.cpp",

		-- 
    	"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",

		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
	}

  	-- 
	includedirs
	{
    	-- 
		"src",

		-- 
    	"vendor/spdlog/include",

    	"%{IncludeDir.GLFW}",
		"%{IncludeDir.GL3W}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
	}

	links
	{
		"GLFW",
		"GL3W",
		"ImGui",
		"opengl32.lib",
	}
  
	-- 
	flags { "NoPCH" }

	-- 当当前系统是windows时
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"GLCORE_PLATFORM_WINDOWS",
      		"GLCORE_ENABLE_ASSERTS",
		}

	-- Debug配置项属性
	filter "configurations:Debug"
		runtime "Debug"
		-- 开启调试符号
		symbols "on"

	-- Release配置项属性
	filter "configurations:Release"
		runtime "Release"
		-- 开启优化参数
		optimize "on"

	-- Dist配置项属性
	filter "configurations:Dist"
		runtime "Release"
		-- 开启优化参数
		optimize "on"