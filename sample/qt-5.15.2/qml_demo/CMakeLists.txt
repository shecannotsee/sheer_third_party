cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "qml_demo")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import qt
# turn on moc to qt object
set(CMAKE_AUTOMOC ON)
# add install path
set(_qt_path "${CMAKE_CURRENT_SOURCE_DIR}/../../../libraries/qt-5.15.2")
# Add to cmake
set(CMAKE_PREFIX_PATH ${_qt_path})
# find Qt and load Qt's CMake config
find_package(Qt5 COMPONENTS Core Quick REQUIRED)

set(qt_include_dir "${_qt_path}/include")
set(qt_lib_dir "${_qt_path}/lib")
set(qt_link_libs Qt5::Core Qt5::Quick)
########################################################################################################################

# include
include_directories()
# lib
link_directories()

file(GLOB_RECURSE SRC
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${CMAKE_SOURCE_DIR}/other_class/*.cpp
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${qt_link_libs})
