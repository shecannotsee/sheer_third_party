cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "spdlog-1.10.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import asio
set(_spdlog_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/spdlog")
set(spdlog_include_dir "${_spdlog_path}/include")
set(spdlog_lib_dir "${_spdlog_path}/lib")
set(spdlog_link_libs spdlog)
########################################################################################################################

# include
include_directories(${spdlog_include_dir})
# lib
link_directories(${spdlog_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${spdlog_link_libs})