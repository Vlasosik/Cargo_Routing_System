#include "service/ServiceContainer.h"

ServiceContainer::ServiceContainer()
    : cargoesService(cargoesDao), driversService(driverDao), routesService(routesDao),
      vehiclesService(vehiclesDao) {
}

ServiceContainer &ServiceContainer::getInstance() {
    static ServiceContainer instance;
    return instance;
}

CargoesService &ServiceContainer::getCargoesService() {
    return cargoesService;
}

DriversService &ServiceContainer::getDriversService() {
    return driversService;
}

RoutesService &ServiceContainer::getRoutesService() {
    return routesService;
}

VehiclesService &ServiceContainer::getVehiclesService() {
    return vehiclesService;
}
