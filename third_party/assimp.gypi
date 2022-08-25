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
            'rapidjson/include',
    	],
		
		'sources': [
            'assimp/code/BaseImporter.cpp',
            'assimp/code/BaseProcess.cpp',
            'assimp/code/BaseProcess.h',
            'assimp/code/DefaultIOStream.cpp',
            'assimp/code/DefaultIOSystem.cpp',
            'assimp/code/DefaultLogger.cpp',
            'assimp/code/ScenePreprocessor.cpp',
            'assimp/code/ScenePreprocessor.h',
            'assimp/code/MaterialSystem.cpp',
            'assimp/code/MaterialSystem.h',
            'assimp/code/ValidateDataStructure.cpp',
            'assimp/code/ValidateDataStructure.h',
            'assimp/code/Importer.cpp',
            'assimp/code/ImporterRegistry.cpp',
            'assimp/code/PostStepRegistry.cpp',
            'assimp/code/ProcessHelper.cpp',
            'assimp/code/ProcessHelper.h',
            'assimp/code/SpatialSort.cpp',
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
            'assimp/code/glTFImporter.h',
            'assimp/code/glTFImporter.cpp',
            'assimp/code/glTF2Importer.h',
            'assimp/code/glTF2Importer.cpp',
            'assimp/code/MakeVerboseFormat.h',
            'assimp/code/MakeVerboseFormat.cpp',
            'assimp/code/CreateAnimMesh.cpp',
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
                    '_SCL_SECURE_NO_WARNINGS',
                    '_CRT_SECURE_NO_WARNINGS',
                    'ASSIMP_BUILD_NO_EXPORT',
                    'ASSIMP_BUILD_NO_C4D_IMPORTER',
                    #'ASSIMP_IMPORTER_GLTF_USE_OPEN3DGC=1',
                    'ASSIMP_BUILD_DLL_EXPORT',
                    
                    # formats to disable
                    'ASSIMP_BUILD_NO_X_IMPORTER',
                    'ASSIMP_BUILD_NO_AMF_IMPORTER',
                    'ASSIMP_BUILD_NO_3DS_IMPORTER',
                    'ASSIMP_BUILD_NO_MD3_IMPORTER',
                    'ASSIMP_BUILD_NO_MDL_IMPORTER',
                    'ASSIMP_BUILD_NO_MD2_IMPORTER',
                    'ASSIMP_BUILD_NO_PLY_IMPORTER',
                    'ASSIMP_BUILD_NO_ASE_IMPORTER',
                    #'ASSIMP_BUILD_NO_OBJ_IMPORTER',
                    'ASSIMP_BUILD_NO_HMP_IMPORTER',
                    'ASSIMP_BUILD_NO_SMD_IMPORTER',
                    'ASSIMP_BUILD_NO_MDC_IMPORTER',
                    'ASSIMP_BUILD_NO_MD5_IMPORTER',
                    'ASSIMP_BUILD_NO_STL_IMPORTER',
                    'ASSIMP_BUILD_NO_LWO_IMPORTER',
                    'ASSIMP_BUILD_NO_DXF_IMPORTER',
                    'ASSIMP_BUILD_NO_NFF_IMPORTER',
                    'ASSIMP_BUILD_NO_RAW_IMPORTER',
                    'ASSIMP_BUILD_NO_SIB_IMPORTER',
                    'ASSIMP_BUILD_NO_OFF_IMPORTER',
                    'ASSIMP_BUILD_NO_AC_IMPORTER',
                    'ASSIMP_BUILD_NO_BVH_IMPORTER',
                    'ASSIMP_BUILD_NO_IRRMESH_IMPORTER',
                    'ASSIMP_BUILD_NO_IRR_IMPORTER',
                    'ASSIMP_BUILD_NO_Q3D_IMPORTER',
                    'ASSIMP_BUILD_NO_B3D_IMPORTER',
                    'ASSIMP_BUILD_NO_COLLADA_IMPORTER',
                    'ASSIMP_BUILD_NO_TERRAGEN_IMPORTER',
                    'ASSIMP_BUILD_NO_CSM_IMPORTER',
                    'ASSIMP_BUILD_NO_3D_IMPORTER',
                    'ASSIMP_BUILD_NO_LWS_IMPORTER',
                    'ASSIMP_BUILD_NO_OGRE_IMPORTER',
                    'ASSIMP_BUILD_NO_OPENGEX_IMPORTER',
                    'ASSIMP_BUILD_NO_MS3D_IMPORTER',
                    'ASSIMP_BUILD_NO_COB_IMPORTER',
                    'ASSIMP_BUILD_NO_BLEND_IMPORTER',
                    'ASSIMP_BUILD_NO_Q3BSP_IMPORTER',
                    'ASSIMP_BUILD_NO_NDO_IMPORTER',
                    'ASSIMP_BUILD_NO_IFC_IMPORTER',
                    'ASSIMP_BUILD_NO_XGL_IMPORTER',
                    'ASSIMP_BUILD_NO_FBX_IMPORTER',
                    'ASSIMP_BUILD_NO_ASSBIN_IMPORTER',
                    #'ASSIMP_BUILD_NO_GLTF_IMPORTER',
                    'ASSIMP_BUILD_NO_3MF_IMPORTER',
                    'ASSIMP_BUILD_NO_X3D_IMPORTER',
                    'ASSIMP_BUILD_NO_MMD_IMPORTER',
                    'ASSIMP_BUILD_NO_STEPFILE_IMPORTER',
                    
                    # postprocess step to disable
                    'ASSIMP_BUILD_NO_MAKELEFTHANDED_PROCESS',
                    'ASSIMP_BUILD_NO_FLIPUVS_PROCESS',
                    'ASSIMP_BUILD_NO_FLIPWINDINGORDER_PROCESS',
                    'ASSIMP_BUILD_NO_CALCTANGENTS_PROCESS',
                    'ASSIMP_BUILD_NO_JOINVERTICES_PROCESS',
                    'ASSIMP_BUILD_NO_TRIANGULATE_PROCESS',
                    'ASSIMP_BUILD_NO_DROPFACENORMALS_PROCESS',
                    'ASSIMP_BUILD_NO_GENFACENORMALS_PROCESS',
                    'ASSIMP_BUILD_NO_GENVERTEXNORMALS_PROCESS',
                    'ASSIMP_BUILD_NO_REMOVEVC_PROCESS',
                    'ASSIMP_BUILD_NO_SPLITLARGEMESHES_PROCESS',
                    'ASSIMP_BUILD_NO_PRETRANSFORMVERTICES_PROCESS',
                    'ASSIMP_BUILD_NO_LIMITBONEWEIGHTS_PROCESS',
                    #'ASSIMP_BUILD_NO_VALIDATEDS_PROCESS',
                    'ASSIMP_BUILD_NO_IMPROVECACHELOCALITY_PROCESS',
                    'ASSIMP_BUILD_NO_FIXINFACINGNORMALS_PROCESS',
                    'ASSIMP_BUILD_NO_REMOVE_REDUNDANTMATERIALS_PROCESS',
                    'ASSIMP_BUILD_NO_EMBEDTEXTURES_PROCESS',
                    'ASSIMP_BUILD_NO_FINDINVALIDDATA_PROCESS',
                    'ASSIMP_BUILD_NO_FINDDEGENERATES_PROCESS',
                    'ASSIMP_BUILD_NO_SORTBYPTYPE_PROCESS',
                    'ASSIMP_BUILD_NO_GENUVCOORDS_PROCESS',
                    'ASSIMP_BUILD_NO_TRANSFORMTEXCOORDS_PROCESS',
                    'ASSIMP_BUILD_NO_FINDINSTANCES_PROCESS',
                    'ASSIMP_BUILD_NO_OPTIMIZEMESHES_PROCESS',
                    'ASSIMP_BUILD_NO_OPTIMIZEGRAPH_PROCESS',
                    'ASSIMP_BUILD_NO_SPLITBYBONECOUNT_PROCESS',
                    'ASSIMP_BUILD_NO_DEBONE_PROCESS',
                    'ASSIMP_BUILD_NO_GLOBALSCALE_PROCESS',
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
