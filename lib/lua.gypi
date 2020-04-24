{
	'includes': [ 'common.gypi', ],

	'variables': {
	},	
	
    'target_defaults': {
        'default_configuration': 'Release',
    }, 

	'targets': [{
		'target_name': 'lua',
		'include_dirs': [
			'lua-5.3.5/src',
    	],

		'sources': [
	        'lua-5.3.5/src/lapi.c',
            'lua-5.3.5/src/lapi.h',
            'lua-5.3.5/src/lauxlib.c',
            'lua-5.3.5/src/lauxlib.h',
            'lua-5.3.5/src/lbaselib.c',
            'lua-5.3.5/src/lbitlib.c',
            'lua-5.3.5/src/lcode.c',
            'lua-5.3.5/src/lcode.h',
            'lua-5.3.5/src/lcorolib.c',
            'lua-5.3.5/src/lctype.c',
            'lua-5.3.5/src/lctype.h',
            'lua-5.3.5/src/ldblib.c',
            'lua-5.3.5/src/ldebug.c',
            'lua-5.3.5/src/ldebug.h',
            'lua-5.3.5/src/ldo.c',
            'lua-5.3.5/src/ldo.h',
            'lua-5.3.5/src/ldump.c',
            'lua-5.3.5/src/lfunc.c',
            'lua-5.3.5/src/lfunc.h',
            'lua-5.3.5/src/lgc.c',
            'lua-5.3.5/src/lgc.h',
            'lua-5.3.5/src/linit.c',
            'lua-5.3.5/src/liolib.c',
            'lua-5.3.5/src/llex.c',
            'lua-5.3.5/src/llex.h',
            'lua-5.3.5/src/llimits.h',
            'lua-5.3.5/src/lmathlib.c',
            'lua-5.3.5/src/lmem.c',
            'lua-5.3.5/src/lmem.h',
            'lua-5.3.5/src/loadlib.c',
            'lua-5.3.5/src/lobject.c',
            'lua-5.3.5/src/lobject.h',
            'lua-5.3.5/src/lopcodes.c',
            'lua-5.3.5/src/lopcodes.h',
            'lua-5.3.5/src/loslib.c',
            'lua-5.3.5/src/lparser.c',
            'lua-5.3.5/src/lparser.h',
            'lua-5.3.5/src/lprefix.h',
            'lua-5.3.5/src/lstate.c',
            'lua-5.3.5/src/lstate.h',
            'lua-5.3.5/src/lstring.c',
            'lua-5.3.5/src/lstring.h',
            'lua-5.3.5/src/lstrlib.c',
            'lua-5.3.5/src/ltable.c',
            'lua-5.3.5/src/ltable.h',
            'lua-5.3.5/src/ltablib.c',
            'lua-5.3.5/src/ltm.c',
            'lua-5.3.5/src/ltm.h',
            'lua-5.3.5/src/lua.h',
            'lua-5.3.5/src/lua.hpp',
            'lua-5.3.5/src/luaconf.h',
            'lua-5.3.5/src/lualib.h',
            'lua-5.3.5/src/lundump.c',
            'lua-5.3.5/src/lundump.h',
            'lua-5.3.5/src/lutf8lib.c',
            'lua-5.3.5/src/lvm.c',
            'lua-5.3.5/src/lvm.h',
            'lua-5.3.5/src/lzio.c',
            'lua-5.3.5/src/lzio.h',
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
				'type': 'static_library',

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
