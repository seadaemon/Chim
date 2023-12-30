cmake_minimum_required (VERSION 3.8)

set(PROJECT_NAME CHIM)
project(${PROJECT_NAME} C CXX)

set(HDRS
	chim.hpp path_config.h
)

set(SRCS 
	main.cpp chim.cpp
)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${SRCS} ${HDRS})

# Find Vulkan Library
find_package(Vulkan REQUIRED FATAL_ERROR)
include_directories(${VULKAN_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
set(VULKAN_LIB_PATH C:/VulkanSDK/1.3.268.0)

# Other libraries
set(LIBRARY_PATH C:/Software/Libraries)
include_directories(${LIBRARY_PATH}/include)

# SDL 2
find_library(SDL2_LIBRARY SDL2 HINT ${VULKAN_LIB_PATH}/Lib)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

if(MSVC)
   set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)
endif()