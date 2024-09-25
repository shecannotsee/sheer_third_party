cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "jsoncpp-1.9.5")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import jsoncpp
set(_jsoncpp_path "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/jsoncpp-1.9.5")
set(jsoncpp_include_dir "${_jsoncpp_path}/include")
set(jsoncpp_lib_dir "${_jsoncpp_path}/lib")
set(jsoncpp_link_libs jsoncpp)
########################################################################################################################

# include
include_directories(${jsoncpp_include_dir})
# lib
link_directories(${jsoncpp_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${jsoncpp_link_libs})