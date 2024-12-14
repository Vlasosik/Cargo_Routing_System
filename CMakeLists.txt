cmake_minimum_required(VERSION 3.29)
project(intelligent_cargo_routing_system)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(core)
add_subdirectory(networking)
add_subdirectory(pch)

include_directories(/opt/homebrew/opt/libpq/include)

link_directories(/opt/homebrew/opt/libpq/lib)

find_library(PQ_LIB pq HINTS /opt/homebrew/opt/libpq/lib REQUIRED)

add_executable(intelligent_cargo_routing_system main.cpp)

target_precompile_headers(intelligent_cargo_routing_system PUBLIC
        ${CMAKE_SOURCE_DIR}/pch/pch.h
)

target_link_libraries(intelligent_cargo_routing_system PRIVATE core pch ${PQ_LIB} networking)