cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "ffmpeg-4.1")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import ffmpeg
set(_ffmpeg_path "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/ffmpeg-4.1")
set(ffmpeg_include_dir "${_ffmpeg_path}/include")
set(ffmpeg_lib_dir "${_ffmpeg_path}/lib")
set(ffmpeg_link_libs avcodec avdevice avfilter avformat avutil postproc swresample swscale)
########################################################################################################################

# include
include_directories(${ffmpeg_include_dir})
# lib
link_directories(${ffmpeg_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread"
        -Wl,--start-group
        ${ffmpeg_link_libs} z jpeg x264 x265 lzma
        -Wl,--end-group
)