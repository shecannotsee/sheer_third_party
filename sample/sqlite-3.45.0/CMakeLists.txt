cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "sqlite-3.45.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import sqlite
set(_sqlite_path "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/sqlite-3.45.0")
set(sqlite_include_dir "${_sqlite_path}/include")
set(sqlite_lib_dir "${_sqlite_path}/lib")
set(sqlite_link_libs sqlite3 dl)
########################################################################################################################

# include
include_directories(${sqlite_include_dir})
# lib
link_directories(${sqlite_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# 链接库
target_link_libraries(${PROJECT_NAME} "-pthread" ${sqlite_link_libs})

