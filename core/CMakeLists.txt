add_library(core STATIC
        src/migration/MigrationSQL.cpp
        include/entity/Drivers.h
        include/entity/Vehicles.h
        include/entity/Cargoes.h
        include/entity/Routes.h
        include/dao/DriverDAO.h
        src/dao/DriverDAO.cpp
        include/dao/CargoesDAO.h
        src/dao/CargoesDAO.cpp
        include/dao/RoutesDAO.h
        src/dao/RoutesDAO.cpp
        include/dao/VehiclesDAO.h
        src/dao/VehiclesDAO.cpp
        include/service/CargoService.h
        src/service/CargoService.cpp
        include/service/DriverService.h
        src/service/DriverService.cpp
        include/service/RouteService.h
        src/service/RouteService.cpp
        include/service/VehicleService.h
        src/service/VehicleService.cpp
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
        ${CMAKE_SOURCE_DIR}/libraries/uuid/include
        ${CMAKE_SOURCE_DIR}/libraries/config/include
        ${CMAKE_SOURCE_DIR}/libraries/type_traits/include
        ${CMAKE_SOURCE_DIR}/libraries/assert/include
)

target_precompile_headers(core PUBLIC ${CMAKE_SOURCE_DIR}/pch/pch.h)

target_link_libraries(core PRIVATE
        pch
        ${PQ_LIB}
)