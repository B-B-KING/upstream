# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2019 Intel Corporation. All Rights Reserved.
cmake_minimum_required(VERSION 3.1.0)

project(realsense)

#set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
# Find librealsense2 installed package

find_package(OpenCV REQUIRED)


# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(OpenGL_GL_PREFERENCE LEGACY)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/usr/local/include/librealsense2/")
#include_directories("/home/tx2/Documents/librealsense")

find_package(realsense2 REQUIRED)
find_package(realsense2-gl REQUIRED)
find_package(OpenGL)
find_package(glfw3)
find_package(Threads REQUIRED)


find_library(DL_LIBS libdl.so)
find_library(X11_LIBS libX11.so)

# Add the application sources to the target
add_executable(${PROJECT_NAME} main.cpp)


# Link librealsense2 to the target
target_link_libraries(${PROJECT_NAME}
                        ${realsense2_LIBRARY}
                        glfw
                        OpenGL::GL
                        OpenGL::GLU
                        realsense2-gl
                        ${OpenCV_LIBS}
                        ${DL_LIBS}
                        ${CMAKE_THREAD_LIBS_INIT}
                        ${X11_LIBS}
                        ${zmqpp_LIBRARIES}
                        zmq
                        )

