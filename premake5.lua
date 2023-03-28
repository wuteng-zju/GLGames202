-- GLGames202 Dependencies
IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/OpenGL/vendor/stb_image"
IncludeDir["GLFW"] = "%{wks.location}/OpenGL/vendor/GLFW/include"
IncludeDir["GL3W"] = "%{wks.location}/OpenGL/vendor/GL3W/include"
IncludeDir["ImGui"] = "%{wks.location}/OpenGL/vendor/ImGui"
IncludeDir["glm"] = "%{wks.location}/OpenGL/vendor/glm"

--workspace 解决方案
workspace "GLGames202"

  -- 启动项目
  startproject "ShadowMap"

  -- 解决方案配置项：Debug、Release、Dist
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

  -- 平台配置
  platforms
  {
    'x64'
  }

  -- x64平台配置属性
  filter "platforms:x64"
    -- 指定架构为x64
    architecture "x64"

  -- 指定输出目录和中间目录的文件夹名称
  outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

  group "Dependencies"
    include "OpenGL/vendor/GLFW"
    include "OpenGL/vendor/GL3W"
    include "OpenGL/vendor/imgui"
  group ""

  group "OpenGL"
    include "OpenGL"
  group ""

  group "1-ShadowMap"
    include "Sources/1-ShadowMap"
  group ""

  group "2-PRT"
    include "Sources/2-PRT"
  group ""

  group "3-SSRT"
    include "Sources/3-SSRT"
  group ""

  group "4-KullaCoutyBRDF"
    include "Sources/4-KullaContyBRDF"
  group ""
