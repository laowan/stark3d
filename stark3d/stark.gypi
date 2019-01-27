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
            'utils/math.h',
            'learnsomething/learnsomething.h',
            'learnsomething/eigen.cpp',
            'learnsomething/thread.cpp',
        ],

        'include_dirs': 
        [
            '../lib/bgfx/include',
            '../lib/glfw/include',
            '../lib/assimp/include',
        ],

        'library_dirs':
        [
            '../lib/bgfx/lib/x86',
        ],

        'dependencies': 
        [
            'glfw',
            'assimp',
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
                                    'bgfxDebug.lib',
                                    'bxDebug.lib',
                                    'bimgDebug.lib',
                                    'bimg_decodeDebug.lib',
                                    'psapi.lib',
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
                                    'bgfxRelease.lib',
                                    'bxRelease.lib',
                                    'bimgRelease.lib',
                                    'bimg_decodeRelease.lib',
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
