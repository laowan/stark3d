cmake_minimum_required(VERSION 3.19)
project(test_vulkan C CXX)

set(TARGET test_vulkan)
set(PUBLIC_HDR_DIR include)

# ==================================================================================================
# Sources and headers
# ==================================================================================================
#set(PUBLIC_HDRS
#    include/stark3d.h)
    
set(SRCS
    main.cpp)

# ==================================================================================================
# Includes & target definition
# ==================================================================================================
# specify where our headers are
include_directories(${PUBLIC_HDR_DIR})
include_directories(${EXTERNAL}/glm-0.9.9.8)
include_directories(${EXTERNAL}/glfw-3.3.8/include)
include_directories(${EXTERNAL}/vulkan/1.3.231.1/Include)

# we're building a library
#add_library(${TARGET} STATIC ${PRIVATE_HDRS} ${PUBLIC_HDRS} ${SRCS})
add_executable(${TARGET} ${SRCS})

# ==================================================================================================
# Dependencies
# ==================================================================================================
#target_include_directories(${PROJECT_NAME} PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}
#    ${CMAKE_CURRENT_SOURCE_DIR}/../framework)

target_link_libraries(${PROJECT_NAME} PRIVATE
	glfw
	${EXTERNAL}/vulkan/1.3.231.1/Lib/vulkan-1.lib)


# ==================================================================================================
# Compiler flags
# ==================================================================================================