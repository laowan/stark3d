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

project "editor"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files {
      "../editor/*.h",
      "../editor/*.cpp",
      "../editor/*.ui",
      QT_GENERATED_MOC_DIR .. '*.cpp',
      QT_GENERATED_UI_DIR .. '*.h',
      QT_GENERATED_QRC_DIR .. '*.cpp',
   }
   
   includedirs {
      QT_GENERATED_UI_DIR,
      QTDIR .. "include",
      QTDIR .. "include/QtCore",
      QTDIR .. "include/QtGui",
      QTDIR .. "include/QtWidgets",
      "../lib/bgfx/include"
   }

   libdirs {
      QTDIR .. "lib",
      "../lib/bgfx/lib/x86"
   }
   
   links {
      "gdi32.lib",
      "psapi.lib",
   }
   
   defines { "_ITERATOR_DEBUG_LEVEL=0" }
      
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      staticruntime "on"
      links {
         "Qt5Cored",
         "Qt5Guid",
         "Qt5Widgetsd",
         "bgfxDebug.lib",
         "bimg_decodeDebug.lib",
         "bimgDebug.lib",
         "bxDebug.lib"
      }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      staticruntime "on"
      links {
         "Qt5Core",
         "Qt5Gui",
         "Qt5Widgets",
         "bgfxRelease.lib",
         "bimg_decodeRelease.lib",
         "bimgRelease.lib",
         "bxRelease.lib"
      }
      
      filter "platforms:x86"
        system "Windows"
        architecture "x86"

      filter "platforms:x86_64"
        system "Windows"
        architecture "x86_64"

   configuration "windows"        
      postbuildcommands {
         --string.format("copy /Y %s %s", QTDIR:gsub('/', '\\').."bin\\Qt5Cored.dll", ".\\bin\\Debug\\Qt5Cored.dll"),
         --string.format("copy /Y %s %s", QTDIR:gsub('/', '\\').."bin\\Qt5Guid.dll", ".\\bin\\Debug\\Qt5Guid.dll"),
         --string.format("copy /Y %s %s", QTDIR:gsub('/', '\\').."bin\\Qt5Widgetsd.dll", ".\\bin\\Debug\\Qt5Widgetsd.dll"),
         string.format('call python ..\\tools\\run_deployqt.py %s .\\bin\\$(Configuration)\\editor.exe', QTDIR:gsub('/', '\\')),
      }