cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "GSL-4.0.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import GSL
set(_GSL_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/GSL")
set(GSL_include_dir "${_GSL_path}/include")
set(GSL_lib_dir)
set(GSL_link_libs)
########################################################################################################################

# include
include_directories(${GSL_include_dir})
# lib
link_directories()

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread")