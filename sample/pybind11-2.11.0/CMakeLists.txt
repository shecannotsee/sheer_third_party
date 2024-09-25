cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "pybind11-2.11.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import pybind11
set(_pybind11_path "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/pybind11-v2.11.0")
set(CMAKE_PREFIX_PATH "${_pybind11_path}")
find_package(pybind11 REQUIRED)
########################################################################################################################

# include
include_directories(${pybind11_include_dir})
# lib
link_directories()

pybind11_add_module(double_vector_1D api_1.cpp)
pybind11_add_module(double_vector_2D api_2.cpp)
pybind11_add_module(sample_cpp_lib sample_cpp_lib.cpp)

list(APPEND api double_vector_1D double_vector_2D)
