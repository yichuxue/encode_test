cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)


SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)


project(fx_convert)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-O0 -g")

include_directories(
	${CMAKE_CURRENT_LIST_DIR}/rockchip
	${CMAKE_CURRENT_LIST_DIR}/package
)

link_directories(
	/usr/local/lib
	${CMAKE_CURRENT_LIST_DIR}/firefly_mpplib
)

set(SOURCE_FILES main.cpp
				package/encode.cpp)

add_executable(fx_convert ${SOURCE_FILES})

# add_library(fx_convert SHARED ${SOURCE_FILES})
# set_target_properties(fx_convert PROPERTIES output_name "fx_convert")

target_link_libraries(fx_convert
		rockchip_mpp
		utils
		opencv_core
		opencv_highgui
		opencv_imgproc
		opencv_imgcodecs
		m
		drm
		rga
		pthread
)
