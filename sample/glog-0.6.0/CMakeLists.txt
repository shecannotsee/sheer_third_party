cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "glog-0.6.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import fmt
set(_glog_path "/home/shecannotsee/desktop/sheer_third_party/libraries/glog")
set(glog_include_dir "${_glog_path}/include")
set(glog_lib_dir "${_glog_path}/lib")
set(glog_link_libs glog)
########################################################################################################################

# include
include_directories(${glog_include_dir})
# lib
link_directories(${glog_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${glog_link_libs})