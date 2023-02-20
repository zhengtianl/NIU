cmake_minimum_required(VERSION 3.17)
project(NIU)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    add_compile_options(/wd4819)#忽略保存为unicode警告
endif ()

include(CMakeLists.txt.glfw)
include_directories("depends")
#源代码文件
add_executable(untitled main.cpp ${glfw_sources} ShaderSource.h VertexData.h)