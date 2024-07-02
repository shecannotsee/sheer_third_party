cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "yaml-cpp-0.8.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import yaml-cpp
set(_yaml-cpp_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/yaml-cpp")
set(yaml-cpp_include_dir "${_yaml-cpp_path}/include")
set(yaml-cpp_lib_dir "${_yaml-cpp_path}/lib")
set(yaml-cpp_link_libs yaml-cpp)
########################################################################################################################

# include
include_directories(${yaml-cpp_include_dir})
# lib
link_directories(${yaml-cpp_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${yaml-cpp_link_libs})