cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "magic_enum-0.9.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import GSL
set(_magic_enum_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/magic_enum")
set(magic_enum_include_dir "${_magic_enum_path}/include")
set(magic_enum_lib_dir)
set(magic_enum_link_libs)
########################################################################################################################

# include
include_directories(${magic_enum_include_dir})
# lib
link_directories()

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread")
