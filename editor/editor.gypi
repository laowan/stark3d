{
    "variables": {
        'QTDIR': 'E:/qt/5.10.1/msvc2017', # modify to your QTDIR.
        "TOOLS_DIR": "./tools",
        "RCC_DEST_DIR": "<(INTERMEDIATE_DIR)/rcc",
        "RCC_FILELIST": [
            #"<(RCC_DEST_DIR)/qrc_filterdesigner.cpp",
            #"<(RCC_DEST_DIR)/qrc_qss.cpp",
        ],
        "UI_DEST_DIR": "<(INTERMEDIATE_DIR)/ui",
        "UI_FILELIST": [
            "<(UI_DEST_DIR)/ui_mainwindow.h",
        ],
        "MOC_SRC_DIR": "<(DEPTH)/src/editor",
        "MOC_DEST_DIR": "<(INTERMEDIATE_DIR)/moc",
        "MOC_FILELIST": [
            "<(MOC_DEST_DIR)/moc_application.cpp",
            "<(MOC_DEST_DIR)/moc_mainwindow.cpp",
        ],
        "conditions": [
            [
                'OS=="win"',
                {
                    "MOC_FILELIST": [
                    ]
                },
            ]
        ],
    },
    "targets": [
        {
            "target_name": "editor",
            "type": "executable",
            "sources": [
                "main.cpp",
                "application.cpp",
                "application.h",
                "mainwindow.cpp",
                "mainwindow.h",
                "mainwindow.ui",
                "editor.qrc",
                "qss.qrc",
                "<@(MOC_FILELIST)",
                "<@(RCC_FILELIST)",
                "<@(UI_FILELIST)",
            ],
            "rules": [
                {
                    "rule_name": "generate_rcc",
                    "extension": "qrc",
                    "outputs": ["<(RCC_DEST_DIR)/qrc_<(RULE_INPUT_ROOT).cpp"],
                    "action": [
                        "<(QTDIR)/bin/rcc",
                        "<(RULE_INPUT_PATH)",
                        "-name",
                        "<(RULE_INPUT_ROOT)",
                        "-o",
                        "<(RCC_DEST_DIR)/qrc_<(RULE_INPUT_ROOT).cpp",
                    ],
                    "message": "Generating qrc_<(RULE_INPUT_ROOT).cpp.",
                    "msvs_cygwin_shell": 0,
                },
                {
                    "rule_name": "generate_ui",
                    "extension": "ui",
                    "outputs": ["<(UI_DEST_DIR)/ui_<(RULE_INPUT_ROOT).h"],
                    "action": [
                        "<(QTDIR)/bin/uic",
                        "<(RULE_INPUT_PATH)",
                        "-o",
                        "<(UI_DEST_DIR)/ui_<(RULE_INPUT_ROOT).h",
                    ],
                    "message": "Generating ui_<(RULE_INPUT_ROOT).h.",
                    "msvs_cygwin_shell": 0,
                },
                {
                    "rule_name": "generate_moc",
                    "extension": "h",
                    "outputs": ["<(MOC_DEST_DIR)/moc_<(RULE_INPUT_ROOT).cpp"],
                    "action": [
                        "<(QTDIR)/bin/moc",
                        "<(RULE_INPUT_PATH)",
                        "-o",
                        "<(MOC_DEST_DIR)/moc_<(RULE_INPUT_ROOT).cpp",
                    ],
                    "message": "Generating moc_<(RULE_INPUT_ROOT).cpp.",
                    "msvs_cygwin_shell": 0,
                },
            ],
            #'msvs_precompiled_header': 'precompiled.h',
            #'msvs_precompiled_source': 'precompiled.cpp',
            # Required so that the printf actually causes a build failure
            # if the pch isn't included.
            #'msvs_settings': {
            # 'VCCLCompilerTool': {
            #    'WarningLevel': '3',
            #   'WarnAsError': 'true',
            #  },
            # },
            "include_dirs": [
                "<(QTDIR)/include",
                "<(QTDIR)/include/QtCore",
                "<(QTDIR)/include/QtGui",
                "<(QTDIR)/include/QtWidgets",
                "./",
                "editor",
                "<(UI_DEST_DIR)",
                "<(RCC_FILELIST)",
            ],
            "library_dirs": [
                "<(QTDIR)/lib",
                "<(PRODUCT_DIR)",
            ],
            "dependencies": [
                #"stark",
            ],
            "conditions": [
                [
                    'OS=="win"',
                    {
                        "defines": [
                            "WIN32",
                            "WIN32_LEAN_AND_MEAN",
                            "_M_IX86",
                        ],
                        "include_dirs": ["../../3rd/Kinect/v2.0_1409/inc"],
                        "library_dirs": ["../../3rd/Kinect/v2.0_1409/lib/x86"],
                        "resource_include_dirs": ["$(ProjectDir)"],
                        "sources": [
                            "editor.rc",
                        ],
                        "configurations": {
                            "Debug": {
                                "msvs_settings": {
                                    "VCCLCompilerTool": {"RuntimeLibrary": "3"},  # /MDd
                                    "VCLinkerTool": {
                                        "ImageHasSafeExceptionHandlers": "false",  # /SAFESEH:NO
                                        "AdditionalDependencies": [
                                            "kernel32.lib",
                                            "user32.lib",
                                            "winmm.lib",
                                            "ole32.lib",
                                            "oleaut32.lib",
                                            "Qt5Cored.lib",
                                            "Qt5Guid.lib",
                                            "Qt5Widgetsd.lib",
                                        ],
                                        "conditions": [
                                        ],
                                    },
                                }  # msvs_settings
                            },  # Debug
                            "Release": {
                                "msvs_settings": {
                                    "VCCLCompilerTool": {"RuntimeLibrary": "2"},  # /MD
                                    "VCLinkerTool": {
                                        "ImageHasSafeExceptionHandlers": "false",  # /SAFESEH:NO
                                        "AdditionalDependencies": [
                                            "kernel32.lib",
                                            "user32.lib",
                                            "winmm.lib",
                                            "ole32.lib",
                                            "oleaut32.lib",
                                            "Qt5Core.lib",
                                            "Qt5Gui.lib",
                                            "Qt5Widgets.lib",
                                        ],
                                        "conditions": [
                                        ],
                                    },
                                }  # msvs_settings
                            },  # Release
                        },  # configurations
                    },
                ],
                [
                    'OS=="mac"',
                    {
                        #'mac_bundle': 1,
                        "include_dirs": [
                            "<(QTDIR)/lib/QtCore.framework/Headers",
                            "<(QTDIR)/lib/QtGUI.framework/Headers",
                            "<(QTDIR)/lib/QtWidgets.framework/Headers",
                            "../inc",
                            "./",
                            "editor",
                            "<(UI_DEST_DIR)",
                            "<(RCC_FILELIST)",
                        ],
                        "link_settings": {
                            "libraries": [
                                "<(QTDIR)/lib/QtCore.framework",
                                "<(QTDIR)/lib/QtGUI.framework",
                                "<(QTDIR)/lib/QtWidgets.framework",
                            ]
                        },
                        "mac_framework_dirs": [
                            "<(QTDIR)/lib",
                            "$(SDKROOT)/System/Library/Frameworks",  # probably the system path is used by default
                        ],
                        "xcode_settings": {
                            "INFOPLIST_FILE": "src/editor/Info.plist",
                            "OTHER_LDFLAGS": [
                                "-headerpad_max_install_names",
                                "-Wl,-rpath,<(QTDIR)/lib",
                                "-F<(QTDIR)/lib",
                            ],
                        },
                    },
                ],
            ],
        },  # target editor.
    ],
}
