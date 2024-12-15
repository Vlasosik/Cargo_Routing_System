#ifndef SERVICECONTAINER_H
#define SERVICECONTAINER_H
#include "CargoesService.h"
#include "DriversService.h"
#include "RoutesService.h"
#include "VehiclesService.h"

class ServiceContainer {
    CargoesService cargoesService;
    DriversService driversService;
    RoutesService routesService;
    VehiclesService vehiclesService;

    CargoesDAO cargoesDao;
    DriverDAO driverDao;
    RoutesDAO routesDao;
    VehiclesDAO vehiclesDao;

    ServiceContainer();

public:
    ServiceContainer(const ServiceContainer &) = delete;

    ServiceContainer &operator=(const ServiceContainer &) = delete;

    static ServiceContainer &getInstance();

    CargoesService &getCargoesService();

    DriversService &getDriversService();

    RoutesService &getRoutesService();

    VehiclesService &getVehiclesService();
};
#endif //SERVICECONTAINER_H
