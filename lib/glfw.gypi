{
	'includes': [ 'common.gypi', ],

	'variables': {
	},	
	
    'target_defaults': {
        'default_configuration': 'Release',
    }, 

	'targets': [{
		'target_name': 'glfw',
		'include_dirs': [
		    'glfw',
    	],
		
		'sources': [
			'glfw/glfw_config.h',
			'glfw/include/GLFW/glfw3.h',
			'glfw/include/GLFW/glfw3native.h',
			'glfw/src/egl_context.h',
			'glfw/src/egl_context.c',
			'glfw/src/internal.h',
			'glfw/src/mappings.h',
			'glfw/src/osmesa_context.h',
			'glfw/src/osmesa_context.c',
			'glfw/src/wgl_context.h',
			'glfw/src/wgl_context.c',
			'glfw/src/win32_joystick.h',
			'glfw/src/win32_platform.h',
			'glfw/src/context.c',
			'glfw/src/init.c',
			'glfw/src/input.c',
			'glfw/src/monitor.c',
			'glfw/src/vulkan.c',
			'glfw/src/window.c',
			'glfw/src/win32_init.c',
			'glfw/src/win32_joystick.c',
			'glfw/src/win32_monitor.c',
			'glfw/src/win32_thread.c',
			'glfw/src/win32_time.c',
			'glfw/src/win32_window.c',
     	],

        'dependencies': [
        ],
		
		'defines':[
		],

        'direct_dependent_settings': 
		{
			'include_dirs': 
			[
				'../inc',
			],
		},
		
		'conditions': [		
			['OS=="win"',
			{
				'defines': [
					'WIN32',
					'WIN32_LEAN_AND_MEAN',
					'_GLFW_USE_CONFIG_H',
					'_CRT_SECURE_NO_WARNINGS',
                    '_HAS_ITERATOR_DEBUGGING=0',
                    '_ITERATOR_DEBUG_LEVEL=0',
				],

				'type': 'static_library',

				'include_dirs': [
				],
				
				'sources!': [
				],

			    'sources': [
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
          				'ExceptionHandling': '2',
        			},

				    'VCLinkerTool': 
				    {
						'AdditionalDependencies': 
						[
						  'user32.lib',
						],
				      
						'AdditionalLibraryDirectories': [
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
          				'ExceptionHandling': '2',
        			},

				    'VCLinkerTool': 
				    {
						'AdditionalDependencies': 
						[
						  'user32.lib',
						],
				      
						'AdditionalLibraryDirectories': [
						],	
				    },
				  }, # msvs_settings
				}, # Release
				}, # configurations          
			}
			],				
			
			['OS=="android"', 
			{
				'type': 'shared_library',

			    'ldflags': [
	  				'-llog',
          		],	

				'defines': [
				],

				'sources': [
				],
				
				'include_dirs': [
				],
				
				'sources!': [
				],

	            'conditions':[
	            ]
			}],	
		
			['OS=="linux"',
			{
				'type': 'static_library',
				'libraries': [
					 ], 
					"cflags": [ "-lpthread","-lX11" ],
						
					'sources': [
					],
					
				'include_dirs': [
	            	'/usr/local/include/',
				],
			}],	
			
			['OS=="ios"',
			{
				'defines': [
					'TARGET_OS_IPHONE',
					'__APPLE__',
				],

				'type': 'static_library',	
				'libraries': [
				 ],
                 
				'sources': [
				],
				
				'include_dirs': [
	                'orangefilter',
				],
				
				'sources!': [
				],
			}],		
		
			['OS=="mac"',
			{
				'defines': [
                    '__APPLE__',
				],

				'type': 'static_library',		
			    'sources': [
			    ],
				
                'include_dirs': [
                ],
				
				'sources!': [
				],
			}],			
		
		],
	},
	],

  } 
