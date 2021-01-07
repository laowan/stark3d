{
  'target_defaults': 
  {
    'includes': 
    [ 
      'stark3d/common.gypi', 
    ],
    'default_configuration': 'Release',
  },

  'conditions': [
    ['OS=="win"',
    {
        'includes':
        [
            'lib/glfw.gypi',
            'lib/assimp.gypi',
            'lib/freetype.gypi',
            'lib/lua.gypi',
            'editor/editor.gypi',
            'stark3d/stark.gypi',
        ],
        'conditions': 
        [
            ['build_type=="win_exe"', 
                {
                    'includes':
                    [
                    ]
                }
            ],
            
            ['opengl_library=="GLEW"', 
                {
                    'includes':
                    [
                        'lib/glew.gypi',
                    ]
                }
            ],
        ],    
    }],

    ['OS=="mac"',
    {
        'includes':
        [
        ]
    }],

    ['OS=="ios"',
    {
        'includes':
        [
        ]
    }],   
  ],
} 
