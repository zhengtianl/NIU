cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    add_compile_options(/wd4819)#忽略保存为unicode警告
endif ()
include(CMakeLists.txt.glfw)
include(CMakeLists.txt.FreeType)
include(CMakeLists.txt.fmod)
#拷贝data文件
file(COPY "../../template/data/images/diffuse_fishsoup_pot.cpt" DESTINATION "../data/images/")
file(COPY "../../template/data/images/urban_128.cpt" DESTINATION "../data/images/")
file(COPY "../../template/data/images/fmod_play_2d_sound_tips.cpt" DESTINATION "../data/images/")
file(COPY "../../template/data/model/fishsoup_pot.mesh" DESTINATION "../data/model/")
file(COPY "../../template/data/shader/unlit.vs" DESTINATION "../data/shader/")
file(COPY "../../template/data/shader/unlit.fs" DESTINATION "../data/shader/")
file(COPY "../../template/data/material/fishsoup_pot.mat" DESTINATION "../data/material/")
file(COPY "../../template/data/material/fmod_play_2d_sound_tips.mat" DESTINATION "../data/material/")
file(COPY "../../template/data/font/" DESTINATION "../data/font/")
file(COPY "../../template/data/audio/fmod_play_wav/" DESTINATION "../data/audio/")


#头文件目录
include_directories("depends")
include_directories("source")

file(GLOB_RECURSE engine_cpp source/*.cpp)
file(GLOB_RECURSE rttr_cpp "depends/rttr/*.cpp")
file(GLOB_RECURSE example_cpp example/*.cpp)

add_executable(untitled ${glfw_sources} ${rttr_cpp} ${freetype_src} ${engine_cpp} ${example_cpp})