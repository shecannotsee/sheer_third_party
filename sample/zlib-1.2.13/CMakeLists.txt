cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "zlib-1.2.13")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import zlib
set(_zlib_cpp_path "/home/shecannotsee/desktop/sheer_third_party/libraries/zlib")
set(zlib_include_dir "${_zlib_path}/include")
set(zlib_lib_dir "${_zlib_path}/lib")
set(zlib_link_libs z)
########################################################################################################################

# include
include_directories(${zlib_include_dir})
# lib
link_directories(${zlib_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${zlib_link_libs})