-- project PRT
project "2-PRT"

	-- 项目类型：控制台程序
	kind "ConsoleApp"

	-- 项目语言：C++
	language "C++"

	 -- 语言标准
	cppdialect "C++17"

	-- 
	staticruntime "on"

	-- 指定输出目录
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

	-- 指定中间目录
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	-- 加载src目录下的所有.h,.cpp文件
	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	-- 
	includedirs
	{
		"%{wks.location}/OpenGL/src",
		"%{wks.location}/OpenGL/vendor",
		"%{wks.location}/OpenGL/vendor/spdlog/include",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GL3W}",
		"%{IncludeDir.ImGui}",
	}

	-- 
	links
	{
		"OpenGL"
	}

	-- Windows平台
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