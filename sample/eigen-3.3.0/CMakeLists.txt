cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "eigen-3.3.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import ffmpeg
set(_eigen_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/eigen")
set(eigen_include_dir "${_eigen_path}/include")
set(eigen_lib_dir)
set(eigen_link_libs)
########################################################################################################################

# include
include_directories(${eigen_include_dir})
# lib
link_directories()

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread")