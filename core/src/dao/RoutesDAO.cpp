#include "dao/RoutesDAO.h"

#include <sqlpp11/select.h>

RoutesDAO::RoutesDAO() {
    sqlpp::postgresql::connection_config config;

    const char *db_user = std::getenv("DB_USER");
    const char *db_password = std::getenv("DB_PASSWORD");
    const char *db_name = std::getenv("DB_NAME");
    const char *db_port = std::getenv("DB_PORT");
    const char *db_host = std::getenv("DB_HOST");

    if (db_user) config.user = db_user;
    if (db_password) config.password = db_password;
    if (db_name) config.dbname = db_name;
    if (db_port) config.port = std::stoi(db_port);
    if (db_host) config.host = db_host;

    db = sqlpp::postgresql::connection(config);
}

void RoutesDAO::createRoutes(const Routes &routes) {
    auto route = mydb::Routes::TabRoutes{};
    auto statement = insert_into(route).set(
        route.driverId = routes.getDriverId(),
        route.vehiclesId = routes.getVehicleId(),
        route.cargoesId = routes.getCargoesId(),
        route.startPoint = routes.getStartPoint(),
        route.endPoint = routes.getEndPoint(),
        route.status = routes.getStatus()
    );
    try {
        db(statement);
        std::cout << "Route successfully created!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

Routes RoutesDAO::getRoutesById(const int64_t &id) {
    if (!isRoutesExist(id)) {
        throw std::invalid_argument("Route doesn`t exist!");
    }
    auto route = mydb::Routes::TabRoutes{};
    auto statement = select(route.id, route.driverId, route.vehiclesId,
                            route.cargoesId, route.startPoint, route.endPoint, route.status, route.createdAt,
                            route.updatedAt).from(route)
            .where(route.id == id);
    auto result = db(statement);
    const auto &row = result.front();
    Routes routes;
    routes.setId(row.id);
    routes.setDriverId(row.driverId);
    routes.setVehicleId(row.vehiclesId);
    routes.setCargoesId(row.cargoesId);
    routes.setStartPoint(row.startPoint);
    routes.setEndPoint(row.endPoint);
    routes.setStatus(row.status);
    routes.setCreatedAt(row.createdAt);
    routes.setUpdatedAt(row.updatedAt);
    return routes;
}

std::vector<Routes> RoutesDAO::getAllRoutes() {
    auto route = mydb::Routes::TabRoutes{};
    auto statement = select(
                route.id, route.driverId, route.vehiclesId, route.cargoesId, route.startPoint, route.endPoint,
                route.status, route.createdAt, route.updatedAt
            ).from(route)
            .where(route.id == 1);

    auto result = db(statement);
    if (result.empty()) {
        throw std::invalid_argument("Routes don`t exist!");
    }
    std::vector<Routes> listRoutes;
    for (const auto &row: result) {
        auto createdAt = static_cast<std::chrono::system_clock::time_point>(row.createdAt);
        auto updatedAt = static_cast<std::chrono::system_clock::time_point>(row.updatedAt);
        listRoutes.emplace_back(
            row.id, row.driverId, row.vehiclesId, row.cargoesId, row.startPoint, row.endPoint,
            row.status, createdAt, updatedAt
        );
    }
    return listRoutes;
}

void RoutesDAO::updateRoutes(const Routes &routes) {
    if (!isRoutesExist(routes.getId())) {
        throw std::invalid_argument("Route doesn`t exist!");
    }
    auto route = mydb::Routes::TabRoutes{};
    auto statement = update(route).set(
        route.driverId = routes.getDriverId(),
        route.vehiclesId = routes.getVehicleId(),
        route.cargoesId = routes.getCargoesId(),
        route.startPoint = routes.getStartPoint(),
        route.endPoint = routes.getEndPoint(),
        route.status = routes.getStatus()
    ).where(route.id == routes.getId());
    try {
        db(statement);
        std::cout << "Route successfully updated!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

void RoutesDAO::deleteRoutes(const int64_t &id) {
    if (!isRoutesExist(id)) {
        throw std::invalid_argument("Route doesn`t exist!");
    }
    auto route = mydb::Routes::TabRoutes{};
    auto statement = remove_from(route).where(route.id == id);
    try {
        db(statement);
        std::cout << "Route successfully deleted!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

bool RoutesDAO::isRoutesExist(const int64_t &id) {
    auto route = mydb::Routes::TabRoutes{};
    auto statement = select(route.id).from(route).where(route.id == id);
    auto result = db(statement);
    return !result.empty();
}
