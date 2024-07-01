cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "nlohmann_json-3.10.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import asio
set(_nlohmann_json_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/nlohmann_json")
set(nlohmann_json_include_dir "${_nlohmann_json_path}/include")
set(nlohmann_json_lib_dir)
set(nlohmann_json_link_libs)
########################################################################################################################

# include
include_directories(${nlohmann_json_include_dir})
# lib
link_directories()

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread")