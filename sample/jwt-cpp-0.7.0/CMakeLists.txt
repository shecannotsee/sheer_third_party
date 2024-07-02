cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "jwt-cpp-0.7.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import openssl
set(_openssl_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/openssl")
set(openssl_include_dir "${_openssl_path}/include")
set(openssl_lib_dir "${_openssl_path}/lib")
set(openssl_link_libs ssl crypto)
########################################################################################################################

########################################################################################################################
# import jwt-cpp
set(_jwt-cpp_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/jwt-cpp")
set(jwt-cpp_include_dir "${_jwt-cpp_path}/include")
set(jwt-cpp_lib_dir)
set(jwt-cpp_link_libs)
########################################################################################################################

# include
include_directories(${openssl_include_dir} ${jwt-cpp_include_dir})
# lib
link_directories(${openssl_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${openssl_link_libs})