cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "paho.mqtt.cpp-1.2.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import openssl
set(_openssl_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/openssl")
set(openssl_include_dir "${_openssl_path}/include")
set(openssl_lib_dir "${_openssl_path}/lib")
set(openssl_link_libs ssl crypto)
########################################################################################################################

########################################################################################################################
# import paho.mqtt.c
set(_paho.mqtt.c_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/paho.mqtt.c")
set(paho.mqtt.c_include_dir "${_paho.mqtt.c_path}/include")
set(paho.mqtt.c_lib_dir "${_paho.mqtt.c_path}/lib")
set(paho.mqtt.c_link_libs paho-mqtt3as paho-mqtt3cs)
########################################################################################################################

########################################################################################################################
# import paho.mqtt.cpp
set(_paho.mqtt.cpp_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/paho.mqtt.cpp")
set(paho.mqtt.cpp_include_dir "${_paho.mqtt.cpp_path}/include")
set(paho.mqtt.cpp_lib_dir "${_paho.mqtt.cpp_path}/lib")
set(paho.mqtt.cpp_link_libs paho-mqttpp3)
########################################################################################################################

# include
include_directories(
        ${openssl_include_dir}
        ${paho.mqtt.c_include_dir}
        ${paho.mqtt.cpp_include_dir})
# lib
link_directories(
        ${openssl_lib_dir}
        ${paho.mqtt.c_lib_dir}
        ${paho.mqtt.cpp_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread"
        ${openssl_link_libs}
        ${paho.mqtt.c_link_libs}
        ${paho.mqtt.cpp_link_libs})