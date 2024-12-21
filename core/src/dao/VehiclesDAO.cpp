#include "dao/VehiclesDAO.h"

#include <sqlpp11/insert.h>
#include <sqlpp11/remove.h>
#include <sqlpp11/select.h>
#include <sqlpp11/update.h>

VehiclesDAO::VehiclesDAO() {
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

void VehiclesDAO::createVehicles(const Vehicles &vehicles) {
    auto vehicle = mydb::Vehicles::TabVehicle{};
    auto statement = insert_into(vehicle).set(
        vehicle.brand = vehicles.getBrand(),
        vehicle.type = vehicles.getType()
    );
    try {
        db(statement);
        std::cout << "Vehicle successfully created!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

Vehicles VehiclesDAO::getVehicleById(const int64_t &id) {
    if (!isVehicleExist(id)) {
        throw std::invalid_argument("Vehicle doesn`t exist!");
    }
    auto vehicle = mydb::Vehicles::TabVehicle{};
    auto statement = select(vehicle.id, vehicle.brand, vehicle.type, vehicle.createdAt, vehicle.updatedAt)
            .from(vehicle).where(vehicle.id == id);
    auto result = db(statement);
    auto &row = result.front();
    Vehicles vehicles;
    vehicles.setId(row.id);
    vehicles.setBrand(row.brand);
    vehicles.setType(row.type);
    vehicles.setCreatedAt(row.createdAt);
    vehicles.setUpdatedAt(row.updatedAt);
    return vehicles;
}

std::vector<Vehicles> VehiclesDAO::getAllVehicle() {
    auto vehicle = mydb::Vehicles::TabVehicle{};
    auto statement = select(
                vehicle.id, vehicle.brand, vehicle.type, vehicle.createdAt, vehicle.updatedAt
            ).from(vehicle)
            .where(vehicle.id == 1);

    auto result = db(statement);
    if (result.empty()) {
        throw std::invalid_argument("Vehicles don`t exist!");
    }
    std::vector<Vehicles> listVehicles;
    for (const auto &row: result) {
        auto createdAt = static_cast<std::chrono::system_clock::time_point>(row.createdAt);
        auto updatedAt = static_cast<std::chrono::system_clock::time_point>(row.updatedAt);
        listVehicles.emplace_back(
            row.id, row.brand, row.type, createdAt, updatedAt
        );
    }
    return listVehicles;
}

void VehiclesDAO::updateVehicle(const Vehicles &vehicles) {
    if (!isVehicleExist(vehicles.getId())) {
        throw std::invalid_argument("Vehicle doesn`t exist!");
    }
    auto vehicle = mydb::Vehicles::TabVehicle{};
    auto statement = update(vehicle).set(
        vehicle.brand = vehicles.getBrand(),
        vehicle.type = vehicles.getType()
    ).where(vehicle.id == vehicles.getId());
    try {
        db(statement);
        std::cout << "Vehicle successfully updated!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

void VehiclesDAO::deleteVehicle(const int64_t &id) {
    if (!isVehicleExist(id)) {
        throw std::invalid_argument("Vehicle doesn`t exist!");
    }
    auto vehicle = mydb::Vehicles::TabVehicle{};
    auto statement = remove_from(vehicle).where(vehicle.id == id);
    try {
        db(statement);
        std::cout << "Vehicle successfully deleted!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

bool VehiclesDAO::isVehicleExist(const int64_t &id) {
    auto vehicle = mydb::Vehicles::TabVehicle{};
    auto statement = select(vehicle.id).from(vehicle).where(vehicle.id == id);
    auto result = db(statement);
    return !result.empty();
}
