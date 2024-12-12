add_library(pch INTERFACE)

target_precompile_headers(pch INTERFACE
        ${CMAKE_SOURCE_DIR}/pch/pch.h
)