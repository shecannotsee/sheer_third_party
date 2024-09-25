cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "asio-1.18.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import asio
set(_asio_path "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/asio-1.18.0")
set(asio_include_dir "${_asio_path}/include")
set(asio_lib_dir)
set(asio_link_libs)
########################################################################################################################

# include
include_directories(${asio_include_dir})
# lib
link_directories()

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread")