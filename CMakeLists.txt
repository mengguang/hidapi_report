cmake_minimum_required(VERSION 3.10)
project(hidapi_report C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(HIDAPI REQUIRED hidapi)

add_executable(hidapi_report main.c)
target_link_libraries(hidapi_report ${HIDAPI_LIBRARIES})
target_include_directories(hidapi_report PUBLIC ${HIDAPI_INCLUDE_DIRS})
target_compile_options(hidapi_report PUBLIC ${HIDAPI_CFLAGS_OTHER})
