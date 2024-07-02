cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "minizip-ng-3.0.9")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import zlib
set(_zlib_cpp_path "/home/shecannotsee/desktop/sheer_third_party/libraries/zlib")
set(zlib_include_dir "${_zlib_path}/include")
set(zlib_lib_dir "${_zlib_path}/lib")
set(zlib_link_libs z)
########################################################################################################################

########################################################################################################################
# import openssl
set(_openssl_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/openssl")
set(openssl_include_dir "${_openssl_path}/include")
set(openssl_lib_dir "${_openssl_path}/lib")
set(openssl_link_libs ssl crypto)
########################################################################################################################

########################################################################################################################
# import GSL
set(_minizip-ng_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/minizip-ng")
set(minizip-ng_include_dir "${_minizip-ng_path}/include")
set(minizip-ng_lib_dir "${_minizip-ng_path}/lib")
set(minizip-ng_link_libs minizip)
########################################################################################################################

# include
include_directories(
        ${zlib_include_dir}
        ${openssl_include_dir}
        ${minizip-ng_include_dir})
# lib
link_directories(
        ${zlib_lib_dir}
        ${openssl_lib_dir}
        ${minizip-ng_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread"
        lzma bz2
        ${zlib_link_libs}
        ${openssl_link_libs}
        ${minizip-ng_link_libs})