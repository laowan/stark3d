{
	'includes': [ 'common.gypi', ],
	'variables': {},	
	'target_defaults': { 'default_configuration': 'Release', }, 
	'targets': [{
		'target_name': 'glew',
		'include_dirs': [ 'glew-2.1.0/include',	],
		'sources': [
			'glew-2.1.0/include/GL/glew.h',
			'glew-2.1.0/include/GL/wglew.h',
            'glew-2.1.0/src/glew.c',
     	],

        'dependencies': [],
		'defines':[ "GLEW_STATIC" ],
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
					#'_CRT_SECURE_NO_WARNINGS',
                    #'_HAS_ITERATOR_DEBUGGING=0',
                    #'_ITERATOR_DEBUG_LEVEL=0',
				],

				'type': 'static_library',
				'include_dirs': [],
				'sources!': [],
			    'sources': [],
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
                          "gdi32.lib",
                          "opengl32.lib",
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
                          "gdi32.lib",
                          "opengl32.lib",
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
