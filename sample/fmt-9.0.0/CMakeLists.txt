cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "fmt-9.0.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import fmt
set(_fmt_path "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/fmt-9.0.0")
set(fmt_include_dir "${_fmt_path}/include")
set(fmt_lib_dir "${_fmt_path}/lib")
set(fmt_link_libs fmt)
########################################################################################################################

# include
include_directories(${fmt_include_dir})
# lib
link_directories(${fmt_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${fmt_link_libs})