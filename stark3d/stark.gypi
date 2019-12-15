{
  'variables': {
      'conditions': [
      ['OS=="win"',
      {
      }]
      ],
  },

  'targets':
  [
    {
        'target_name': 'stark',
        'type': 'executable',
        'sources': 
        [
            'main.cpp',
            'tiny_obj_loader.h',
            'global.h',
            'softrenderer.h',
            'softrenderer.cpp',
            'resources.h',
            'resources.cpp',
            'utils/gldefine.h',
            'utils/linmath.h',
            'utils/math.h',
            'utils/utils.h',
            'utils/utils.cpp',
            'utils/texture.h',
            'utils/texture.cpp',
            'utils/shader.h',
            'utils/shader.cpp',
            'utils/shadermanager.h',
            'utils/shadermanager.cpp',
            'utils/renderdevice.h',
            'utils/renderdevice.cpp',
            'utils/resourcemanager.h',
            'utils/resourcemanager.cpp',
            'scene/world.h',
            'scene/world.cpp',
            'scene/camera.h',
            'scene/camera.cpp',
            'scene/mesh.h',
            'scene/mesh.cpp',
            'external/edtaa3func/edtaa3func.h',
            'external/edtaa3func/edtaa3func.cpp',
            'learnsomething/learnsomething.h',
            'learnsomething/eigen.cpp',
            'learnsomething/thread.cpp',
            'learnsomething/sdf.cpp',
            'learnsomething/raytracing.cpp',
        ],

        'include_dirs': 
        [
            '.',
            '../lib/glfw/include',
            '../lib/assimp/include',
            '../lib/freetype/include',
            '../lib/stb',
            '../lib/glew-2.1.0/include',
        ],

        'library_dirs':
        [
            #'../lib/bgfx/lib/x86', 
        ],

        'dependencies': 
        [
            'glew',
            'glfw',
            'assimp',
            'freetype',
        ],

        'conditions': 
        [
            ['OS=="win"',
            {
                'defines': 
                [
                    'WIN32',
                    'WIN32_LEAN_AND_MEAN',
                    '_HAS_ITERATOR_DEBUGGING=0',
                    '_ITERATOR_DEBUG_LEVEL=0',
                    #'BX_PLATFORM_WINDOWS',
                ],

                'resource_include_dirs': 
                [
                  '$(ProjectDir)',
                ],

                'sources': 
                [
                ],

                'configurations':
                {
                    'Debug':
                    {
                        'msvs_settings':
                        {
                            'VCCLCompilerTool': 
                            {
                              'RuntimeLibrary': '1',  # /MTd
                              'WarnAsError': 'false',
                            },
                            
                            'VCLinkerTool':
                            {
                                'AdditionalDependencies':
                                [
                                    #'bgfxDebug.lib',
                                    #'bxDebug.lib',
                                    #'bimgDebug.lib',
                                    #'bimg_decodeDebug.lib',
                                    'psapi.lib',
                                    'opengl32.lib',
                                    #'msvcrt.lib',
                                    '%(AdditionalDependencies)',
                                ],
                            },
                        }, # msvs_settings
                    }, # Debug
                    
                    'Release':
                    {
                        'msvs_settings':
                        {
                            'VCCLCompilerTool': 
                            {
                              'RuntimeLibrary': '2'  # /MD
                            },

                            'VCLinkerTool':
                            {
                                'AdditionalDependencies':
                                [
                                    #'bgfxRelease.lib',
                                    #'bxRelease.lib',
                                    #'bimgRelease.lib',
                                    #'bimg_decodeRelease.lib',
                                    'psapi.lib',
                                    'msvcrt.lib',
                                ],
                            },
                        }, # msvs_settings
                    }, # Release
                }, # configurations
            }],
        ],
    }, # target TrainDDE.
  ],
}
