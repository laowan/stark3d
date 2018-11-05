{
    'target_defaults': {
        'conditions': [
            ['opengl_library=="PVR_GLES"', 
                {
                    'defines': 
                    [
                        'USE_GLES_LIBRARY',
                    ],
                }
            ],

            ['OS=="linux"', {
            'defines': [
            '__unix__',
            '_LINUX',
            'OF_LINUX'
            ],
            'cflags': [
            '-Wall'
            ]
            }],

            ['OS=="win"', {
            'defines': [
            'WIN32',
            'OF_WIN32',
            'OF_USE_GLES3',
            'OF_USE_GLES31',
            'GL_GLEXT_PROTOTYPES',
            ],

            'msvs_configuration_attributes': {
            'CharacterSet': '0'
            },
            'msvs_settings': {
            'VCCLCompilerTool': {
            #'WarningLevel': '4',
            'WarnAsError': 'true',
            'DisableSpecificWarnings': ['4819'],
            'Detect64BitPortabilityProblems': 'true'
            }
            }
            }],
            ['OS=="ios"', {
            'defines': [
            'OF_IOS',
            'OF_USE_GLES3',
            'GL_GLEXT_PROTOTYPES',
            ],
            }],
            ['OS=="mac"', {
            'defines': [
            '__unix__',
            '_MACOS',
            'OF_MAC',
            'OF_USE_GLES3',
            'OF_USE_GLES31',            
            'GL_GLEXT_PROTOTYPES',
            ],
            'cflags': [
            '-Wall'
            ]
            }]
        ],

        'configurations': {
            'Debug': {
                'defines': [
                '_DEBUG'
                ],
                'conditions': [
                ['OS=="linux" or OS=="freebsd" or OS=="openbsd"', {
                'cflags': [
                '-g'
                ]
                }],
                ['OS=="win"', {
                'msvs_settings': {
                'VCCLCompilerTool': {
                'Optimization': '0',
                'MinimalRebuild': 'true',
                'BasicRuntimeChecks': '3',
                'DebugInformationFormat': '4',

                'conditions': [
                ['library=="shared_library"', {
                'RuntimeLibrary': '3'  # /MDd
                }, {
                'RuntimeLibrary': '1'  # /MTd
                }]
                ]
                },
                'VCLinkerTool': {
                'GenerateDebugInformation': 'true',
                'LinkIncremental': '2'
                }
                }
                }],
                ['OS=="mac"', {
                'xcode_settings': {
                "GCC_OPTIMIZATION_LEVEL": "0",
                'GCC_GENERATE_DEBUGGING_SYMBOLS': 'YES',
                'CLANG_CXX_LANGUAGE_STANDARD' : 'c++11'
                }
                }],
                
                ['OS=="ios"', {
                "defines": [
                    "DEBUG"
                ],

                'xcode_settings': {
                    'SDKROOT': 'iphoneos',
                    'TARGETED_DEVICE_FAMILY': '1,2',
                    'CODE_SIGN_IDENTITY': 'iPhone Developer',
                    'IPHONEOS_DEPLOYMENT_TARGET': '8.0',
                    'ARCHS': '$(ARCHS_STANDARD)',
                    'VALID_ARCHS': 'arm64 armv7 armv7s',
                    'CLANG_ENABLE_OBJC_ARC': 'YES',
                    'CLANG_CXX_LANGUAGE_STANDARD' : 'c++11',
                    'GCC_C_LANGUAGE_STANDARD': 'c11',
                    'GCC_OPTIMIZATION_LEVEL': '0',
                    'GCC_GENERATE_DEBUGGING_SYMBOLS': 'YES',
                    'LD_GENERATE_MAP_FILE' : 'YES',
                    'CONFIGURATION_BUILD_DIR':'build/$(CONFIGURATION)$(EFFECTIVE_PLATFORM_NAME)/libs',
                    # 'PRODUCT_BUNDLE_IDENTIFIER': 'com.yy.orangefilter',
                    'CURRENT_PROJECT_VERSION': 1,
                    'CURRENT_LIBRARY_VERSION': 1,
                    'ENABLE_BITCODE': 'NO',
                    'DYLIB_INSTALL_NAME_BASE': '@rpath'
                }
                }]                
                
                ]
            },

            'Release': {
                'conditions': [
                ['OS=="linux" or OS=="freebsd" or OS=="openbsd"', {
                'cflags': [
                '-O3'
                ]
                }],
                ['OS=="win"', {
                'msvs_settings': {
                'VCCLCompilerTool': {
                'Optimization': '2',

                'conditions': [
                ['library=="shared_library"', {
                'RuntimeLibrary': '2'  # /MD
                }, {
                'RuntimeLibrary': '0'  # /MT
                }]
                ]
                },
                'VCLinkerTool': {
                'GenerateDebugInformation': 'true',
                'LinkIncremental': '2'
                }
                }
                }],
                ['OS=="mac"', {
                'xcode_settings': {
                'GCC_GENERATE_DEBUGGING_SYMBOLS': 'NO',
                'GCC_OPTIMIZATION_LEVEL': '3',
                'CLANG_CXX_LANGUAGE_STANDARD' : 'c++11',
                # -fstrict-aliasing. Mainline gcc enables
                # this at -O2 and above, but Apple gcc does
                # not unless it is specified explicitly.
                'GCC_STRICT_ALIASING': 'YES'
                }
                }],
                
                ['OS=="ios"', {
                
                "defines": [
                    "NDEBUG"
                ],

                # 'mac_framework_dirs': [
                #     '$(SDKROOT)/../../Frameworks',
                # ],

                'xcode_settings': {
                    'SDKROOT': 'iphoneos',
                    'TARGETED_DEVICE_FAMILY': '1,2',
                    'CODE_SIGN_IDENTITY': 'iPhone Developer',
                    'IPHONEOS_DEPLOYMENT_TARGET': '8.0',
                    'ARCHS': '$(ARCHS_STANDARD)',
                    'VALID_ARCHS': 'arm64 armv7 armv7s',
                    'CLANG_ENABLE_OBJC_ARC': 'YES',
                    'CLANG_CXX_LANGUAGE_STANDARD' : 'c++11',                
                    'GCC_C_LANGUAGE_STANDARD': 'c11',
                    'DEAD_CODE_STRIPPING': 'YES',
                    'GCC_INLINES_ARE_PRIVATE_EXTERN': 'YES',
                    'GCC_OPTIMIZATION_LEVEL': '3',
                    'GCC_GENERATE_DEBUGGING_SYMBOLS': 'YES',
                    'LD_GENERATE_MAP_FILE' : 'YES',
                    'CONFIGURATION_BUILD_DIR':'build/$(CONFIGURATION)$(EFFECTIVE_PLATFORM_NAME)/libs',
                    # 'PRODUCT_BUNDLE_IDENTIFIER': 'com.yy.orangefilter',
                    'CURRENT_PROJECT_VERSION': 1,
                    'CURRENT_LIBRARY_VERSION': 1,
                    'ENABLE_BITCODE': 'NO',
                    'DYLIB_INSTALL_NAME_BASE': '@rpath',
                    'DEPLOYMENT_POSTPROCESSING': 'YES',
                    'STRIP_INSTALLED_PRODUCT': 'YES',
                    'STRIP_STYLE': 'non-global',
                    'COPY_PHASE_STRIP': 'YES'
                }
                }]
                
                ]
            }
        }
    },
}
