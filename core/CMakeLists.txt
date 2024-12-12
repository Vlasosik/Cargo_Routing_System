add_library(core STATIC
        src/migration/MigrationSQL.cpp
)

include_directories(/opt/homebrew/opt/libpq/include)

link_directories(/opt/homebrew/opt/libpq/lib)

find_library(PQ_LIB pq HINTS /opt/homebrew/opt/libpq/lib REQUIRED)

target_include_directories(core PUBLIC
        ${CMAKE_SOURCE_DIR}/core/include
        ${CMAKE_SOURCE_DIR}/pch
)

target_include_directories(core PUBLIC
        ${CMAKE_SOURCE_DIR}/libraries/asio/include
        ${CMAKE_SOURCE_DIR}/libraries/date/include
        ${CMAKE_SOURCE_DIR}/libraries/sqlpp11/include
        ${CMAKE_SOURCE_DIR}/libraries/sqlpp11-connector-postgresql/include
        ${CMAKE_SOURCE_DIR}/libraries/poco/Net/include
        ${CMAKE_SOURCE_DIR}/libraries/poco/JSON/include
        ${CMAKE_SOURCE_DIR}/libraries/poco/Foundation/include
)

target_precompile_headers(core PUBLIC ${CMAKE_SOURCE_DIR}/pch/pch.h)

target_link_libraries(core PRIVATE
        pch
        ${PQ_LIB}
)