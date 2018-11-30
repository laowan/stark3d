{
	'includes': [ 'common.gypi', ],

	'variables': {
	},	
	
    'target_defaults': {
        'default_configuration': 'Release',
    }, 

	'targets': [{
		'target_name': 'assimp',
		'include_dirs': [
		    'assimp/include',
    	],
		
		'sources': [
            'assimp/code/BaseImporter.cpp',
            'assimp/code/BaseProcess.cpp',
            'assimp/code/BaseProcess.h',
            'assimp/code/DefaultIOStream.cpp',
            'assimp/code/DefaultIOSystem.cpp',
            'assimp/code/Importer.cpp',
            'assimp/code/scene.cpp',
            'assimp/code/Version.cpp',
            'assimp/code/ObjFileData.h',
            'assimp/code/ObjFileImporter.cpp',
            'assimp/code/ObjFileImporter.h',
            'assimp/code/ObjFileMtlImporter.cpp',
            'assimp/code/ObjFileMtlImporter.h',
            'assimp/code/ObjFileParser.cpp',
            'assimp/code/ObjFileParser.h',
            'assimp/code/ObjTools.h',
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
					'_CRT_SECURE_NO_WARNINGS',
                    '_HAS_ITERATOR_DEBUGGING=0',
                    '_ITERATOR_DEBUG_LEVEL=0',
                    'ASSIMP_BUILD_NO_EXPORT',
                    'ASSIMP_BUILD_NO_C4D_IMPORTER',
                    'ASSIMP_IMPORTER_GLTF_USE_OPEN3DGC=1',
                    'ASSIMP_BUILD_DLL_EXPORT',
                    '_SCL_SECURE_NO_WARNINGS',
                    '_CRT_SECURE_NO_WARNINGS',
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
