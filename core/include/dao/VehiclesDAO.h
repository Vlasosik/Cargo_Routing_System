#ifndef VEHICLESDAO_H
#define VEHICLESDAO_H
#include <sqlpp11/postgresql/connection.h>

#include "entity/Vehicles.h"

class VehiclesDAO {
    sqlpp::postgresql::connection db;
public:
    VehiclesDAO();

    void createVehicles(const Vehicles &vehicles);

    int64_t getVehicleById(const int64_t &id);

    std::vector<Vehicles> getAllVehicle();

    void updateVehicle(const Vehicles &vehicles);

    void deleteVehicle(const int64_t &id);

    bool isVehicleExist(const int64_t &id);
};
#endif //VEHICLESDAO_H
