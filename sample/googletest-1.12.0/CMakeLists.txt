cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "googletest-1.12.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import gtest
set(_gtest_path "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/googletest-1.12.0")
set(gtest_include_dir "${_gtest_path}/include")
set(gtest_lib_dir "${_gtest_path}/lib")
set(gtest_link_libs gmock gtest)
########################################################################################################################

# include
include_directories(${gtest_include_dir})
# lib
link_directories(${gtest_lib_dir})

file(GLOB_RECURSE SRC "${CMAKE_SOURCE_DIR}/main.cpp" "${CMAKE_SOURCE_DIR}/t1_gtest_basic.cpp"
        "${CMAKE_SOURCE_DIR}/t2_gmock_easy.cpp" "${CMAKE_SOURCE_DIR}/t3_gmock_complex.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${gtest_link_libs})