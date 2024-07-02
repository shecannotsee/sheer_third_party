cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "fltk-1.3.7")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import fltk
set(_fltk_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/fltk")
set(fltk_include_dir "${_fltk_path}/include")
set(fltk_lib_dir "${_fltk_path}/lib")
set(fltk_link_libs fltk fltk_gl)
########################################################################################################################

# include
include_directories(${fltk_include_dir})
# lib
link_directories(${fltk_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${fltk_link_libs}
        "-lX11 -ldl -lGL -lXfixes -lXrender -lXcursor -lXft -lXinerama -lXext -lfontconfig")