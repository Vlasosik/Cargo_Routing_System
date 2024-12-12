#include "dao/DriverDAO.h"

#include <sqlpp11/insert.h>
#include <sqlpp11/remove.h>
#include <sqlpp11/select.h>
#include <sqlpp11/postgresql/update.h>

DriverDAO::DriverDAO() {
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

void DriverDAO::createDriver(const TabDrivers &driver) {
    auto drivers = mydb::Drivers::TabDrivers{};
    const auto statement = insert_into(drivers).set(
        drivers.firstName = driver.firstName,
        drivers.lastName = driver.lastName,
        drivers.phone = driver.phone
    );
    try {
        db(statement);
        std::cout << "Driver successfully created!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

int64_t DriverDAO::getDriverId(const int64_t &id) {
    if (!isDriverExist(id)) {
        std::cout << "Driver doesn`t exist!" << std::endl;
    }
    auto drivers = mydb::Drivers::TabDrivers{};
    auto statement = sqlpp::select(drivers.id).from(drivers).where(drivers.id == id);
    auto result = db(statement);
    return result.front().id;
}

std::vector<TabDrivers> DriverDAO::getAllDrivers() {
    auto drivers = mydb::Drivers::TabDrivers{};
    auto statement = sqlpp::select(
        drivers.id, drivers.firstName, drivers.lastName, drivers.phone, drivers.createdAt, drivers.updated_at
    ).from(drivers)
    .where(drivers.id == 1);

    auto result = db(statement);
    std::vector<TabDrivers> listDrivers;
    for (const auto& row : result) {
        auto createdAt = static_cast<std::chrono::system_clock::time_point>(row.createdAt);
        auto updatedAt = static_cast<std::chrono::system_clock::time_point>(row.updated_at);
        listDrivers.emplace_back(
            row.id, row.firstName, row.lastName, row.phone, createdAt, updatedAt
        );
    }
    return listDrivers;
}

void DriverDAO::updateDriver(const TabDrivers& driver) {
    if (!isDriverExist(driver.id)) {
        std::cout << "Driver doesn`t exist!" << std::endl;
    }
    auto drivers = mydb::Drivers::TabDrivers{};
    auto statement = update(drivers).set(
        drivers.firstName = driver.firstName,
        drivers.lastName = driver.lastName,
        drivers.phone = driver.phone,
        drivers.createdAt = driver.createdAt,
        drivers.updated_at = driver.updatedAt
    ).where(drivers.id == driver.id);
    try {
        db(statement);
        std::cout << "Driver successfully updated!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

void DriverDAO::deleteDriver(const int64_t &id) {
    if (!isDriverExist(id)) {
        std::cout << "Driver doesn`t exist!" << std::endl;
    }
    auto drivers = mydb::Drivers::TabDrivers{};
    auto statement = remove_from(drivers).where(drivers.id == id);
    try {
        db(statement);
        std::cout << "Driver successfully deleted!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

bool DriverDAO::isDriverExist(const int64_t &id) {
    auto drivers = mydb::Drivers::TabDrivers{};
    auto statement = select(drivers.id).from(drivers).where(drivers.id == id);
    auto result = db(statement);
    return !result.empty();
}
