-- premake5.lua
local QTDIR = "E:/qt_5.15/5.15.2/msvc2019/"
local QT_GENERATED_MOC_DIR = "./generated/moc/"
local QT_GENERATED_UI_DIR = "./generated/ui/"
local QT_GENERATED_QRC_DIR = "./generated/qrc/"

workspace "stark3d"
    configurations { "Debug", "Release" }
    platforms { "x86" } --, "x86_64" }

-- lua
project "lua"
    kind "StaticLib"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    
    files {
        "../lib/lua-5.3.5/src/*.h",
        "../lib/lua-5.3.5/src/*.c",
    }
    
    includedirs {
        "../lib/lua-5.3.5"
    }

-- glfw
project "glfw"
    kind "StaticLib"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    
    files {
        "../lib/glfw/src/context.c",
        "../lib/glfw/src/egl_context.c",
        "../lib/glfw/src/init.c",
        "../lib/glfw/src/input.c",
        "../lib/glfw/src/monitor.c",
        "../lib/glfw/src/osmesa_context.c",
        "../lib/glfw/src/vulkan.c",
        "../lib/glfw/src/wgl_context.c",
        "../lib/glfw/src/win32_init.c",
        "../lib/glfw/src/win32_joystick.c",
        "../lib/glfw/src/win32_monitor.c",
        "../lib/glfw/src/win32_thread.c",
        "../lib/glfw/src/win32_time.c",
        "../lib/glfw/src/win32_window.c",
        "../lib/glfw/src/window.c",
    }
    
    includedirs {
        "../lib/glfw/include",
        "../lib/glfw",
    }
    
    defines { "_GLFW_USE_CONFIG_H" }

-- glew
project "glew"
   kind "SharedLib"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"
   
   files {
      "../lib/glew-2.1.0/include/GL/glew.h",
      "../lib/glew-2.1.0/include/GL/wglew.h",
      "../lib/glew-2.1.0/src/glew.c",
   }
   
   includedirs {
      "../lib/glew-2.1.0/include"
   }
   
   links {
      "opengl32.lib",
      "user32.lib",
      "gdi32.lib",
   }
   
   defines { "GLEW_BUILD" }
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

-- fmt
--project "fmt"
--   kind "StaticLib"
--   language "C++"
--   targetdir "bin/%{cfg.buildcfg}"
--   
--   files {
--      "../lib/fmt/src/*.cc",
--   }
--   
--   includedirs {
--      "../lib/fmt/include"
--   }
--   
--   filter "configurations:Debug"
--      defines { "DEBUG" }
--      symbols "On"
--
--   filter "configurations:Release"
--      defines { "NDEBUG" }
--      optimize "On"
      
-- freetype
project "freetype"
    kind "StaticLib"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    
    files {
        '../lib/freetype/include/**.h',
		'../lib/freetype/src/**.h',
		'../lib/freetype/src/autofit/autofit.c',
		'../lib/freetype/src/base/ftbase.c',
		'../lib/freetype/src/base/ftbbox.c',
		'../lib/freetype/src/base/ftbdf.c',
		'../lib/freetype/src/base/ftbitmap.c',
		'../lib/freetype/src/base/ftcid.c',
		'../lib/freetype/src/base/ftdebug.c',
		'../lib/freetype/src/base/ftfntfmt.c',
		'../lib/freetype/src/base/ftfstype.c',
		'../lib/freetype/src/base/ftgasp.c',
		'../lib/freetype/src/base/ftglyph.c',
		'../lib/freetype/src/base/ftgxval.c',
		'../lib/freetype/src/base/ftinit.c',
		'../lib/freetype/src/base/ftlcdfil.c',
		'../lib/freetype/src/base/ftmm.c',
		'../lib/freetype/src/base/ftotval.c',
		'../lib/freetype/src/base/ftpatent.c',
		'../lib/freetype/src/base/ftpfr.c',
		'../lib/freetype/src/base/ftstroke.c',
		'../lib/freetype/src/base/ftsynth.c',
		'../lib/freetype/src/base/ftsystem.c',
		'../lib/freetype/src/base/fttype1.c',
		'../lib/freetype/src/base/ftwinfnt.c',
		'../lib/freetype/src/bdf/bdf.c',
		'../lib/freetype/src/bzip2/ftbzip2.c',
		'../lib/freetype/src/cache/ftcache.c',
		'../lib/freetype/src/cff/cff.c',
		'../lib/freetype/src/cid/type1cid.c',
		'../lib/freetype/src/gzip/ftgzip.c',
		'../lib/freetype/src/lzw/ftlzw.c',
		'../lib/freetype/src/pcf/pcf.c',
		'../lib/freetype/src/pfr/pfr.c',
		'../lib/freetype/src/psaux/psaux.c',
		'../lib/freetype/src/pshinter/pshinter.c',
		'../lib/freetype/src/psnames/psnames.c',
		'../lib/freetype/src/raster/raster.c',
		'../lib/freetype/src/sfnt/sfnt.c',
		'../lib/freetype/src/smooth/smooth.c',
		'../lib/freetype/src/truetype/truetype.c',
		'../lib/freetype/src/type1/type1.c',
		'../lib/freetype/src/type42/type42.c',
		'../lib/freetype/src/winfonts/winfnt.c',
    }
    
    includedirs {
        "../lib/freetype/include",
    }
    
    defines { "FT2_BUILD_LIBRARY" }

-- stark
project "stark"
    kind "WindowedApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    
    files {
        "../stark3d/scene/*.h",
        "../stark3d/scene/*.cpp",
        "../stark3d/graphics/*.h",
        "../stark3d/graphics/*.cpp",
        "../stark3d/utils/math.h",
        "../stark3d/utils/fileutils.h",
        "../stark3d/utils/fileutils.cpp",
        "../stark3d/utils/data.h",
        "../stark3d/utils/data.cpp",
        "../stark3d/utils/log.h",
        "../stark3d/utils/log.cpp",
        "../stark3d/engine.h",
        "../stark3d/engine.cpp",
        "../stark3d/global.h",
        "../stark3d/stark3d.h",
        "../stark3d/main.cpp",
    }
    
    includedirs {
        "../stark3d",
        "../lib/glew-2.1.0/include",
        "../lib/lua-5.3.5/src",
        "../lib/fmt/include",
        "../lib/fmtlog",
        "../lib/stb"
    }
    
    links {
        "glew",
        "lua",
        "opengl32.lib",
    }
    
-- app
project "app"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    
    files {
        "../app/*.cpp"
    }
    
    includedirs {
        "../lib/glew-2.1.0/include",
        "../lib/glfw/include",
        "../lib/freetype/include",
        "../lib/vulkan/1.2.135.0/Include",
        "../stark3d"
    }
    
    libdirs {
        "bin/%{cfg.buildcfg}",
        "../lib/vulkan/1.2.135.0/Lib32"
    }
    
    links {
        "glew",
        "freetype",
        "glfw",
        "stark",
        "gdi32.lib",
        "psapi.lib",
        "opengl32.lib",
        "glu32.lib",
        "vulkan-1.lib"
    }
 
-- assimp
--[[
project "assimp"
    kind "StaticLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    includedirs {
        '../lib/assimp-5.2.0/include',
        '../lib/assimp-5.2.0/contrib/',
        '../lib/assimp-5.2.0/contrib/pugixml/src',
        '../lib/assimp-5.2.0/contrib/unzip/',
        '../lib/assimp-5.2.0/contrib/zlib/',
        '../lib/assimp-5.2.0/contrib/rapidjson/include/',
        '../lib/assimp-5.2.0/code'
    }
    files {
        -- Dependencies
        '../lib/assimp-5.2.0/contrib/unzip/**',
        '../lib/assimp-5.2.0/contrib/pugixml/**',
        '../lib/assimp-5.2.0/contrib/zlib/*',
        -- Common
        '../lib/assimp-5.2.0/code/Common/**',
        '../lib/assimp-5.2.0/code/PostProcessing/**',
        '../lib/assimp-5.2.0/code/Material/**',
        '../lib/assimp-5.2.0/code/CApi/**',
        -- Importers
        '../lib/assimp-5.2.0/code/AssetLib/Obj/**',
        -- 'assimp/code/Blender/**', 'assimp/contrib/poly2tri/poly2tri/**',
        '../lib/assimp-5.2.0/code/AssetLib/FBX/**',
        '../lib/assimp-5.2.0/code/AssetLib/glTF2/**',
        '../lib/assimp-5.2.0/code/AssetLib/glTF/**',
    }
    -- Importers
    defines {
        '_CRT_SECURE_NO_WARNINGS',
        'ASSIMP_BUILD_NO_3D_IMPORTER',
        'ASSIMP_BUILD_NO_3DS_IMPORTER',
        'ASSIMP_BUILD_NO_3MF_IMPORTER',
        'ASSIMP_BUILD_NO_AC_IMPORTER',
        'ASSIMP_BUILD_NO_AMF_IMPORTER',
        'ASSIMP_BUILD_NO_ASE_IMPORTER',
        'ASSIMP_BUILD_NO_ASSBIN_IMPORTER',
        'ASSIMP_BUILD_NO_B3D_IMPORTER',
        'ASSIMP_BUILD_NO_BLEND_IMPORTER',
        'ASSIMP_BUILD_NO_BVH_IMPORTER',
        'ASSIMP_BUILD_NO_C4D_IMPORTER',
        'ASSIMP_BUILD_NO_COB_IMPORTER',
        'ASSIMP_BUILD_NO_COLLADA_IMPORTER',
        'ASSIMP_BUILD_NO_CSM_IMPORTER',
        'ASSIMP_BUILD_NO_DXF_IMPORTER',
        -- 'ASSIMP_BUILD_NO_FBX_IMPORTER',
        -- 'ASSIMP_BUILD_NO_GLTF_IMPORTER',
        'ASSIMP_BUILD_NO_HMP_IMPORTER',
        'ASSIMP_BUILD_NO_IFC_IMPORTER',
        'ASSIMP_BUILD_NO_IRR_IMPORTER',
        'ASSIMP_BUILD_NO_IRRMESH_IMPORTER',
        'ASSIMP_BUILD_NO_LWO_IMPORTER',
        'ASSIMP_BUILD_NO_LWS_IMPORTER',
        'ASSIMP_BUILD_NO_M3D_IMPORTER',
        'ASSIMP_BUILD_NO_MD2_IMPORTER',
        'ASSIMP_BUILD_NO_MD3_IMPORTER',
        'ASSIMP_BUILD_NO_MD5_IMPORTER',
        'ASSIMP_BUILD_NO_MDC_IMPORTER',
        'ASSIMP_BUILD_NO_MDL_IMPORTER',
        'ASSIMP_BUILD_NO_MMD_IMPORTER',
        'ASSIMP_BUILD_NO_MS3D_IMPORTER',
        'ASSIMP_BUILD_NO_NDO_IMPORTER',
        'ASSIMP_BUILD_NO_NFF_IMPORTER',
        -- 'ASSIMP_BUILD_NO_OBJ_IMPORTER',
        'ASSIMP_BUILD_NO_OFF_IMPORTER',
        'ASSIMP_BUILD_NO_OGRE_IMPORTER',
        'ASSIMP_BUILD_NO_OPENGEX_IMPORTER',
        'ASSIMP_BUILD_NO_PLY_IMPORTER',
        'ASSIMP_BUILD_NO_Q3BSP_IMPORTER',
        'ASSIMP_BUILD_NO_Q3D_IMPORTER',
        'ASSIMP_BUILD_NO_RAW_IMPORTER',
        'ASSIMP_BUILD_NO_SIB_IMPORTER',
        'ASSIMP_BUILD_NO_SMD_IMPORTER',
        'ASSIMP_BUILD_NO_STEP_IMPORTER',
        'ASSIMP_BUILD_NO_STL_IMPORTER',
        'ASSIMP_BUILD_NO_TERRAGEN_IMPORTER',
        'ASSIMP_BUILD_NO_X_IMPORTER',
        'ASSIMP_BUILD_NO_X3D_IMPORTER',
        'ASSIMP_BUILD_NO_XGL_IMPORTER',
        'ASSIMP_BUILD_NO_IQM_IMPORTER'
    }
    -- Exporters
    defines {
        'ASSIMP_BUILD_NO_COLLADA_EXPORTER',
        'ASSIMP_BUILD_NO_X_EXPORTER',
        'ASSIMP_BUILD_NO_STEP_EXPORTER',
        'ASSIMP_BUILD_NO_OBJ_EXPORTER',
        'ASSIMP_BUILD_NO_STL_EXPORTER',
        'ASSIMP_BUILD_NO_PLY_EXPORTER',
        'ASSIMP_BUILD_NO_3DS_EXPORTER',
        'ASSIMP_BUILD_NO_GLTF_EXPORTER',
        'ASSIMP_BUILD_NO_ASSBIN_EXPORTER',
        'ASSIMP_BUILD_NO_ASSXML_EXPORTER',
        'ASSIMP_BUILD_NO_X3D_EXPORTER',
        'ASSIMP_BUILD_NO_FBX_EXPORTER',
        'ASSIMP_BUILD_NO_M3D_EXPORTER',
        'ASSIMP_BUILD_NO_3MF_EXPORTER',
        'ASSIMP_BUILD_NO_ASSJSON_EXPORTER',
        'ASSIMP_BUILD_NO_PBRT_EXPORTER',
        'ASSIMP_BUILD_NO_ASSBIN_EXPORTER',
        'ASSIMP_BUILD_NO_PBRT_EXPORTER'
    }
 --]]