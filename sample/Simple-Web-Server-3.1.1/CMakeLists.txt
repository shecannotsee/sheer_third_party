cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "Simple-Web-Server-3.1.1")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import boost
set(_boost_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/boost")
find_package(Boost REQUIRED COMPONENTS system filesystem PATHS ${_boost_path})
set(boost_include_dir ${Boost_INCLUDE_DIRS})
set(boost_lib_dir)
set(boost_link_libs ${Boost_LIBRARIES})
########################################################################################################################

########################################################################################################################
# import openssl
set(_openssl_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/openssl")
set(openssl_include_dir "${_openssl_path}/include")
set(openssl_lib_dir)
set(openssl_link_libs ssl crypto)
########################################################################################################################

########################################################################################################################
# import Simple-Web-Server
set(_Simple-Web-Server_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/Simple-Web-Server")
set(Simple-Web-Server_include_dir "${_Simple-Web-Server_path}/include/simple-web-server")
set(Simple-Web-Server_lib_dir)
set(Simple-Web-Server_link_libs)
########################################################################################################################


# include
include_directories(${boost_include_dir}  ${openssl_include_dir} ${Simple-Web-Server_include_dir})
# lib
link_directories(${openssl_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${boost_link_libs} ${openssl_link_libs})