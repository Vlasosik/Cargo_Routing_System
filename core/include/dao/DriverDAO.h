#ifndef DRIVERDAO_H
#define DRIVERDAO_H
#include <sqlpp11/postgresql/postgresql.h>

#include "entity/Drivers.h"

class DriverDAO {
    sqlpp::postgresql::connection db;

public:
    DriverDAO();

    void createDriver(const TabDrivers& driver);

    int64_t getDriverId(const int64_t &id);

    std::vector<TabDrivers> getAllDrivers();

    void updateDriver(const TabDrivers& driver);

    void deleteDriver(const int64_t &id);

    bool isDriverExist(const int64_t &id);
};
#endif //DRIVERDAO_H
