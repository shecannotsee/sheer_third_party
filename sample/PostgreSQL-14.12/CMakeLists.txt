cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "pgsql_client_test")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import pagsql
set(_pgsql_path "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/PostgreSQL-14.12")
set(pgsql_include_dir "${_pgsql_path}/include")
set(pgsql_lib_dir "${_pgsql_path}/lib")
set(pgsql_link_libs pq)
########################################################################################################################

# include
include_directories(${pgsql_include_dir})
# lib
link_directories(${pgsql_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# 链接库
target_link_libraries(${PROJECT_NAME} "-pthread" ${pgsql_link_libs})

