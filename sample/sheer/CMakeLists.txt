cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "sheer")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import she_test
set(_sheer_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/sheer/sheer")
set(sheer_include_dir "${_sheer_path}/include")
set(sheer_lib_dir "${_sheer_path}/lib")
set(sheer_link_libs libsheer.a)
########################################################################################################################

# include
include_directories(${sheer_include_dir})
# lib
link_directories(${sheer_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${sheer_link_libs})
