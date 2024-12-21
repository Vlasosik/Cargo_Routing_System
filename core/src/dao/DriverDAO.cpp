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

void DriverDAO::createDriver(const Drivers &driver) {
    auto drivers = mydb::Drivers::TabDrivers{};
    const auto statement = insert_into(drivers).set(
        drivers.firstName = driver.getFirstName(),
        drivers.lastName = driver.getLastName(),
        drivers.phone = driver.getPhone()
    );
    try {
        db(statement);
        std::cout << "Driver successfully created!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

Drivers DriverDAO::getDriverById(const int64_t &id) {
    if (!isDriverExist(id)) {
        throw std::invalid_argument("Driver doesn`t exist!");
    }
    auto drivers = mydb::Drivers::TabDrivers{};
    auto statement = sqlpp::select(drivers.id, drivers.firstName, drivers.lastName, drivers.phone, drivers.createdAt,
                                   drivers.updatedAt).from(drivers).where(drivers.id == id);
    auto result = db(statement);
    const auto &row = result.front();
    Drivers driver;
    driver.setId(row.id);
    driver.setFirstName(row.firstName);
    driver.setLastName(row.lastName);
    driver.setPhone(row.phone);
    driver.setCreatedAt(row.createdAt);
    driver.setUpdatedAt(row.updatedAt);
    return driver;
}

std::vector<Drivers> DriverDAO::getAllDrivers() {
    auto drivers = mydb::Drivers::TabDrivers{};
    auto statement = sqlpp::select(
                drivers.id, drivers.firstName, drivers.lastName, drivers.phone, drivers.createdAt, drivers.updatedAt
            ).from(drivers)
            .where(drivers.id == 1);

    auto result = db(statement);
    if (result.empty()) {
        throw std::invalid_argument("Drivers don`t exist!");
    }
    std::vector<Drivers> listDrivers;
    for (const auto &row: result) {
        auto createdAt = static_cast<std::chrono::system_clock::time_point>(row.createdAt);
        auto updatedAt = static_cast<std::chrono::system_clock::time_point>(row.updatedAt);
        listDrivers.emplace_back(
            row.id, row.firstName, row.lastName, row.phone, createdAt, updatedAt
        );
    }
    return listDrivers;
}

void DriverDAO::updateDriver(const Drivers &driver) {
    if (!isDriverExist(driver.getId())) {
        throw std::invalid_argument("Driver doesn`t exist!");
    }
    auto drivers = mydb::Drivers::TabDrivers{};
    auto statement = update(drivers).set(
        drivers.firstName = driver.getFirstName(),
        drivers.lastName = driver.getLastName(),
        drivers.phone = driver.getPhone(),
        drivers.createdAt = driver.getCreatedAt(),
        drivers.updatedAt = driver.getUpdatedAt()
    ).where(drivers.id == driver.getId());
    try {
        db(statement);
        std::cout << "Driver successfully updated!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

void DriverDAO::deleteDriver(const int64_t &id) {
    if (!isDriverExist(id)) {
        throw std::invalid_argument("Driver doesn`t exist!");
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

bool DriverDAO::isPhoneExist(const std::string &phone) {
    auto drivers = mydb::Drivers::TabDrivers{};
    auto statement = select(drivers.phone).from(drivers).where(drivers.phone == phone);
    auto result = db(statement);
    return !result.empty();
}
