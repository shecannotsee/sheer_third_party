cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "libpqxx-7.9.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import libpg
set(_libpq_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/PostgreSQL")
set(libpq_include_dir "${_libpq_path}/include")
set(libpq_lib_dir "${_libpq_path}/lib")
set(libpq_link_libs pq)
########################################################################################################################

########################################################################################################################
# import libpqxx
set(_libpqxx_path "/home/shecannotsee/Desktop/sheer_third_party/libraries/libpqxx")
set(libpqxx_include_dir "${_libpqxx_path}/include")
set(libpqxx_lib_dir "${_libpqxx_path}/lib")
set(libpqxx_link_libs pqxx)
########################################################################################################################

# include
include_directories(${libpqxx_include_dir})
# lib
link_directories(${libpq_lib_dir} ${libpqxx_lib_dir})

file(GLOB_RECURSE SRC
        "${CMAKE_SOURCE_DIR}/main.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} "-pthread" ${libpq_link_libs} ${libpqxx_link_libs})
