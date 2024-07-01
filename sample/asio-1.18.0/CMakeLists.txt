cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "asio-1.18.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

# import asio
set(asio_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/asio")
set(asio_include_dir "${asio_path}/include")

# include
include_directories(${asio_include_dir})
# lib
link_directories()

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# 链接库
target_link_libraries(${PROJECT_NAME} "-pthread")