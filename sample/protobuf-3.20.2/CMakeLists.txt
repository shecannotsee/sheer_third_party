cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "openssl-1.1.1")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import protobuf
set(_protobuf_path "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/protobuf-v3.20.2")
set(protobuf_include_dir "${_protobuf_path}/include")
set(protobuf_lib_dir "${_protobuf_path}/lib")
set(protobuf_link_libs protobuf)
########################################################################################################################

# include
include_directories(${protobuf_include_dir})
# lib
link_directories(${protobuf_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp" "${CMAKE_SOURCE_DIR}/protobuf/*"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${protobuf_link_libs})