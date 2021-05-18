-- premake5.lua
local QTDIR = "E:/qt_5.15/5.15.2/msvc2019/"
local QT_GENERATED_MOC_DIR = "./generated/moc/"
local QT_GENERATED_UI_DIR = "./generated/ui/"
local QT_GENERATED_QRC_DIR = "./generated/qrc/"

workspace "stark3d"
   configurations { "Debug", "Release" }
   platforms { "x86" } --, "x86_64" }
   
local function executeQtMocOrUICommand(command, files, absoluteDir, filePrefix, fileExtension)
    if type(files) ~= 'table' then return end

    for i, file in ipairs(files) do
        local baseName = filePrefix .. path.getbasename(file)
        local fileStat = os.stat(file)

        print('==> Found different timestamp: ' .. file)
        local command = string.format('%sbin/%s %s -o %s', QTDIR, command, file, absoluteDir .. '/' .. baseName .. fileExtension)
        print('==> ' .. command)
        os.execute(command)
    end
end

local function executeQtQrcCommand(command, files, absoluteDir, filePrefix, fileExtension)
    if type(files) ~= 'table' then
        return
    end

    for i, file in ipairs(files) do
        local baseName = path.getbasename(file)
        local baseNameWithPrefix = filePrefix .. baseName
        local fileStat = os.stat(file)
        
        print('==> Found different timestamp: ' .. file)
        local command = string.format('%sbin/%s %s -name %s -o %s', QTDIR, command, file, baseName, absoluteDir .. '/' .. baseNameWithPrefix .. fileExtension)
        print('==> ' .. command)
        os.execute(command)
    end
end

local mocHeaders = {
   "../editor/mainwindow.h",
   "../editor/renderpanel.h",
}

local uiResFiles = {
   "../editor/mainwindow.ui",
}

local qrcFiles = {
   "../editor/editor.qrc"
}

os.mkdir("./generated/moc")
os.mkdir("./generated/ui")
os.mkdir("./generated/qrc")
executeQtMocOrUICommand('moc', mocHeaders, QT_GENERATED_MOC_DIR, 'moc_', '.cpp')
executeQtMocOrUICommand('uic', uiResFiles, QT_GENERATED_UI_DIR, 'ui_', '.h')
executeQtQrcCommand('rcc', qrcFiles, QT_GENERATED_QRC_DIR, 'qrc_', '.cpp')

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
    
project "stark"
    kind "StaticLib"
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
        "../stark3d/engine.h",
        "../stark3d/engine.cpp",
        "../stark3d/global.h",
        "../stark3d/stark3d.h",
    }
    
    includedirs {
        "../stark3d",
        "../lib/glew-2.1.0/include",
    }
    
    links {
        "glew",
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
        "../stark3d"
    }
    
    libdirs {
        "bin/%{cfg.buildcfg}"
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
    }

--project "editor"
--   kind "ConsoleApp"
--   language "C++"
--   targetdir "bin/%{cfg.buildcfg}"
--
--   files {
--      "../editor/*.h",
--      "../editor/*.cpp",
--      "../editor/*.ui",
--      QT_GENERATED_MOC_DIR .. '*.cpp',
--      QT_GENERATED_UI_DIR .. '*.h',
--      QT_GENERATED_QRC_DIR .. '*.cpp',
--   }
--   
--   includedirs {
--      QT_GENERATED_UI_DIR,
--      QTDIR .. "include",
--      QTDIR .. "include/QtCore",
--      QTDIR .. "include/QtGui",
--      QTDIR .. "include/QtWidgets",
--      "../lib/bgfx/include",
--      "../lib/glew-2.1.0/include",
--      "../lib/freetype/include"
--   }
--
--   libdirs {
--      QTDIR .. "lib",
--      "../lib/bgfx/lib/x86",
--      "bin/%{cfg.buildcfg}"
--   }
--   
--   links {
--      "gdi32.lib",
--      "psapi.lib",
--      "glew.lib",
--      "opengl32.lib",
--      "glu32.lib",
--      "freetype.lib"
--   }
--   
--   defines { "_ITERATOR_DEBUG_LEVEL=0" }
--      
--   filter "configurations:Debug"
--      defines { "DEBUG" }
--      symbols "On"
--      staticruntime "on"
--      links {
--         "Qt5Cored",
--         "Qt5Guid",
--         "Qt5Widgetsd",
--      }
--
--   filter "configurations:Release"
--      defines { "NDEBUG" }
--      optimize "On"
--      staticruntime "on"
--      links {
--         "Qt5Core",
--         "Qt5Gui",
--         "Qt5Widgets",
--      }
--      
--      filter "platforms:x86"
--        system "Windows"
--        architecture "x86"
--
--      filter "platforms:x86_64"
--        system "Windows"
--        architecture "x86_64"
--
--   configuration "windows"        
--      postbuildcommands {
--         --string.format("copy /Y %s %s", QTDIR:gsub('/', '\\').."bin\\Qt5Cored.dll", ".\\bin\\Debug\\Qt5Cored.dll"),
--         --string.format("copy /Y %s %s", QTDIR:gsub('/', '\\').."bin\\Qt5Guid.dll", ".\\bin\\Debug\\Qt5Guid.dll"),
--         --string.format("copy /Y %s %s", QTDIR:gsub('/', '\\').."bin\\Qt5Widgetsd.dll", ".\\bin\\Debug\\Qt5Widgetsd.dll"),
--         string.format('call python ..\\tools\\run_deployqt.py %s .\\bin\\$(Configuration)\\editor.exe', QTDIR:gsub('/', '\\')),
--      }
 