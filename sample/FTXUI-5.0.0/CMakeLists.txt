cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "FTXUI-5.0.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import FTXUI
set(_FTXUI_path "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/FTXUI-v5.0.0")
set(FTXUI_include_dir "${_FTXUI_path}/include")
set(FTXUI_lib_dir "${_FTXUI_path}/lib")
set(FTXUI_link_libs ftxui-component ftxui-dom ftxui-screen)
########################################################################################################################

# include
include_directories(${FTXUI_include_dir})
# lib
link_directories(${FTXUI_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${FTXUI_link_libs})