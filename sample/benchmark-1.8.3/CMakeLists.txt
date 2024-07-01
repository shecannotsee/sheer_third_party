cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "benchmark-1.8.3")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import asio
set(_benchmark_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/benchmark")
set(benchmark_include_dir "${_benchmark_path}/include")
set(benchmark_lib_dir "${_benchmark_path}/lib")
set(benchmark_link_libs benchmark benchmark_main)
########################################################################################################################

# include
include_directories(${benchmark_include_dir})
# lib
link_directories(${benchmark_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${benchmark_link_libs})