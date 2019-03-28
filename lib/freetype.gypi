{
	'includes': [ 'common.gypi', ],

	'variables': {
		'FREETYPE_FILELIST': [
        ],
	},	
	
    'target_defaults': {
        'default_configuration': 'Release',
    }, 

	'targets': [{
		'target_name': 'freetype',
		'include_dirs': [
			'freetype',
            'freetype/include',
    	],

		'sources': [
			#'<@(FREETYPE_FILELIST)',
            'freetype/include/freetype/config/ftconfig.h',
            'freetype/include/freetype/config/ftheader.h',
            'freetype/include/freetype/config/ftmodule.h',
            'freetype/include/freetype/config/ftoption.h',
            'freetype/include/freetype/config/ftstdlib.h',
            'freetype/include/ft2build.h',
            'freetype/src/autofit/autofit.c',
            'freetype/src/base/ftbase.c',
            'freetype/src/base/ftbbox.c',
            'freetype/src/base/ftbdf.c',
            'freetype/src/base/ftbitmap.c',
            'freetype/src/base/ftcid.c',
            'freetype/src/base/ftdebug.c',
            'freetype/src/base/ftfntfmt.c',
            'freetype/src/base/ftfstype.c',
            'freetype/src/base/ftgasp.c',
            'freetype/src/base/ftglyph.c',
            'freetype/src/base/ftgxval.c',
            'freetype/src/base/ftinit.c',
            'freetype/src/base/ftlcdfil.c',
            'freetype/src/base/ftmm.c',
            'freetype/src/base/ftotval.c',
            'freetype/src/base/ftpatent.c',
            'freetype/src/base/ftpfr.c',
            'freetype/src/base/ftstroke.c',
            'freetype/src/base/ftsynth.c',
            'freetype/src/base/ftsystem.c',
            'freetype/src/base/fttype1.c',
            'freetype/src/base/ftwinfnt.c',
            'freetype/src/bdf/bdf.c',
            'freetype/src/bzip2/ftbzip2.c',
            'freetype/src/cache/ftcache.c',
            'freetype/src/cff/cff.c',
            'freetype/src/cid/type1cid.c',
            'freetype/src/gzip/ftgzip.c',
            'freetype/src/lzw/ftlzw.c',
            'freetype/src/pcf/pcf.c',
            'freetype/src/pfr/pfr.c',
            'freetype/src/psaux/psaux.c',
            'freetype/src/pshinter/pshinter.c',
            'freetype/src/psnames/psnames.c',
            'freetype/src/raster/raster.c',
            'freetype/src/sfnt/sfnt.c',
            'freetype/src/smooth/smooth.c',
            'freetype/src/truetype/truetype.c',
            'freetype/src/type1/type1.c',
            'freetype/src/type42/type42.c',
            'freetype/src/winfonts/winfnt.c',
     	],

        # 'dependencies': [
        #   'zlib',
        # ],

		'defines':[
            'FT2_BUILD_LIBRARY',
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
