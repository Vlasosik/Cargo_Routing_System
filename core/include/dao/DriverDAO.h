#ifndef DRIVERDAO_H
#define DRIVERDAO_H
#include <sqlpp11/postgresql/postgresql.h>

#include "entity/Drivers.h"

class DriverDAO {
    sqlpp::postgresql::connection db;

public:
    DriverDAO();

    void createDriver(const Drivers& driver);

    Drivers getDriverById(const int64_t &id);

    std::vector<Drivers> getAllDrivers();

    void updateDriver(const Drivers& driver);

    void deleteDriver(const int64_t &id);

    bool isDriverExist(const int64_t &id);

    bool isPhoneExist(const std::string &phone);
};
#endif //DRIVERDAO_H
