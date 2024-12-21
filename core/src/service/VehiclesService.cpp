 #include "service/VehiclesService.h"

 VehiclesService::VehiclesService(VehiclesDAO &vehiclesDao) : vehiclesDao(vehiclesDao) {
 }

 void VehiclesService::createVehicle(const Vehicles &vehicles) const {
     vehiclesDao.createVehicles(vehicles);
 }

 Vehicles VehiclesService::getVehicleById(const int64_t id) const {
     return vehiclesDao.getVehicleById(id);
 }

 std::vector<Vehicles> VehiclesService::getAllVehicles() const {
     return vehiclesDao.getAllVehicle();
 }

 void VehiclesService::updateVehicle(const Vehicles &vehicles) const {
     vehiclesDao.updateVehicle(vehicles);
 }

 void VehiclesService::deleteVehicle(const int64_t id) const {
     vehiclesDao.deleteVehicle(id);
 }

 bool VehiclesService::isVehicleByIdExist(const int64_t id) const {
     return vehiclesDao.isVehicleExist(id);
 }
