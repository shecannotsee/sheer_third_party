cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "she_ini_parse-0.0.1")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import she_ini_parse
set(_she_ini_parse_path "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/she_ini_parse-v0.0.1")
set(she_ini_parse_include_dir "${_she_ini_parse_path}/include")
set(she_ini_parse_lib_dir "${_she_ini_parse_path}/lib")
set(she_ini_parse_link_libs she_ini_parse)
########################################################################################################################

# include
include_directories(${she_ini_parse_include_dir})
# lib
link_directories(${she_ini_parse_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${she_ini_parse_link_libs})