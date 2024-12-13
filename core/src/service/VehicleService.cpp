 #include "service/VehicleService.h"

 VehicleService::VehicleService(VehiclesDAO &vehiclesDao) : vehiclesDao(vehiclesDao) {
 }

 void VehicleService::createVehicle(const Vehicles &vehicles) const {
     if (vehicles.id <= 0) {
         throw std::invalid_argument("Id must be greater than zero.");
     }
     vehiclesDao.createVehicles(vehicles);
 }

 int64_t VehicleService::getVehicleById(const int64_t id) const {
     return vehiclesDao.getVehicleById(id);
 }

 std::vector<Vehicles> VehicleService::getAllVehicles() const {
     return vehiclesDao.getAllVehicle();
 }

 void VehicleService::updateVehicle(const Vehicles &vehicles) const {
//     VehicleValidate::validateForUpdate(vehicles);
     vehiclesDao.updateVehicle(vehicles);
 }

 void VehicleService::deleteVehicle(const int64_t id) const {
     vehiclesDao.deleteVehicle(id);
 }

 bool VehicleService::isVehicleByIdExist(const int64_t id) const {
     return vehiclesDao.isVehicleExist(id);
 }
