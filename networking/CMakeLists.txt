add_library(networking STATIC
        include/http_server/HttpServer.h
        src/http_server/HttpServer.cpp
        include/factory/RequestHandlerFactory.h
        src/factory/RequestHandlerFactory.cpp
        include/factory/RequestHandlerCargoes.h
        src/factory/RequestHandlerCargoes.cpp
        src/response/JsonCargoesResponse.cpp
        include/response/JsonCargoesResponse.h
        include/factory/RequestHandlerRoutes.h
        src/factory/RequestHandlerRoutes.cpp
        include/response/JsonRoutesResponse.h
        src/response/JsonRoutesResponse.cpp
)

include_directories(/opt/homebrew/opt/libpq/include)

link_directories(/opt/homebrew/opt/libpq/lib)

find_library(PQ_LIB pq HINTS /opt/homebrew/opt/libpq/lib REQUIRED)

target_include_directories(networking PUBLIC
        ${CMAKE_SOURCE_DIR}/networking/include
        ${CMAKE_SOURCE_DIR}/core/include
        ${CMAKE_SOURCE_DIR}/pch
        ${CMAKE_SOURCE_DIR}/libraries/date/include
        ${CMAKE_SOURCE_DIR}/libraries/sqlpp11/include
        ${CMAKE_SOURCE_DIR}/libraries/sqlpp11-connector-postgresql/include
        ${CMAKE_SOURCE_DIR}/libraries/uuid/include
        ${CMAKE_SOURCE_DIR}/libraries/config/include
        ${CMAKE_SOURCE_DIR}/libraries/type_traits/include
        ${CMAKE_SOURCE_DIR}/libraries/assert/include
        /opt/homebrew/Cellar/poco/1.14.0/include
)

target_precompile_headers(networking PUBLIC ${CMAKE_SOURCE_DIR}/pch/pch.h)

target_link_libraries(networking PRIVATE pch
        /opt/homebrew/Cellar/poco/1.14.0/lib/libPocoJSON.110.dylib
        /opt/homebrew/Cellar/poco/1.14.0/lib/libPocoNet.110.dylib
        /opt/homebrew/Cellar/poco/1.14.0/lib/libPocoFoundation.110.dylib
        ${PQ_LIB}
)
