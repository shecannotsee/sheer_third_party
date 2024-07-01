cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "yaml_cpp-0.8.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import spdlog
set(_yaml_cpp_path "/home/shecannotsee/desktop/sheer_third_party/libraries/yaml_cpp")
set(yaml_cpp_include_dir "${_yaml_cpp_path}/include")
set(yaml_cpp_lib_dir "${_yaml_cpp_path}/lib")
set(yaml_cpp_link_libs yaml-cpp)
########################################################################################################################

# include
include_directories(${yaml_cpp_include_dir})
# lib
link_directories(${yaml_cpp_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${yaml_cpp_link_libs})