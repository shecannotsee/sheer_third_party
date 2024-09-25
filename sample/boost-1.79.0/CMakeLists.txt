cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "boost-1.79.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import boost
set(_boost_path "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/boost-1.79.0")
find_package(Boost REQUIRED COMPONENTS system filesystem PATHS ${_boost_path})
set(boost_include_dir ${Boost_INCLUDE_DIRS})
set(boost_lib_dir)
set(boost_link_libs ${Boost_LIBRARIES})
########################################################################################################################

# include
include_directories(${boost_include_dir})
# lib
link_directories()

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${boost_link_libs})