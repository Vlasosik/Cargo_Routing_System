add_library(networking STATIC
        include/http_server/HttpServer.h
        src/http_server/HttpServer.cpp
        include/factory/RequestHandlerFactory.h
        src/factory/RequestHandlerFactory.cpp
        include/factory/RequestHandlerCargoes.h
        src/factory/RequestHandlerCargoes.cpp
)

target_include_directories(networking PUBLIC
        ${CMAKE_SOURCE_DIR}/networking/include
        ${CMAKE_SOURCE_DIR}/pch
        /opt/homebrew/Cellar/poco/1.14.0/include
)

target_precompile_headers(networking PUBLIC ${CMAKE_SOURCE_DIR}/pch/pch.h)

target_link_libraries(networking PRIVATE pch
        /opt/homebrew/Cellar/poco/1.14.0/lib/libPocoJSON.110.dylib
        /opt/homebrew/Cellar/poco/1.14.0/lib/libPocoNet.110.dylib
        /opt/homebrew/Cellar/poco/1.14.0/lib/libPocoFoundation.110.dylib
)
