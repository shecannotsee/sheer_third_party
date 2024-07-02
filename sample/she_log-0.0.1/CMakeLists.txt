cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "she_log-0.0.1")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import she_log
set(_she_log_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/she_log")
set(she_log_include_dir "${_she_log_path}/include")
set(she_log_lib_dir "${_she_log_path}/lib")
set(she_log_link_libs she_log)
########################################################################################################################

# include
include_directories(${she_log_include_dir})
# lib
link_directories(${she_log_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${she_log_link_libs})