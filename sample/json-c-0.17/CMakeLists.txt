cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "json-c-0.17")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import GSL
set(_json-c_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/json-c")
set(json-c_include_dir "${_json-c_path}/include")
set(json-c_lib_dir "${_json-c_path}/lib")
set(json-c_link_libs json-c)
########################################################################################################################

# include
include_directories(${json-c_include_dir})
# lib
link_directories(${json-c_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${json-c_link_libs})