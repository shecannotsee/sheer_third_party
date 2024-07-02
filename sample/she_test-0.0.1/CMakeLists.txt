cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "she_test-0.0.1")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import she_test
set(_she_test_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/she_test")
set(she_test_include_dir "${_she_test_path}/include")
set(she_test_lib_dir)
set(she_test_link_libs)
########################################################################################################################

# include
include_directories(${she_test_include_dir})
# lib
link_directories()

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp" "${CMAKE_SOURCE_DIR}/suite1.cpp" "${CMAKE_SOURCE_DIR}/suite2.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread")