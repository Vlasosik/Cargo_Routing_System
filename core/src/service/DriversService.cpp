 #include "service/DriversService.h"

 DriversService::DriversService(DriverDAO &driverDao) : driverDao(driverDao) {
 }

 void DriversService::createDriver(const Drivers &drivers) const {
     if (drivers.getId() <= 0) {
         throw std::invalid_argument("Id must be greater than zero.");
     }
     if (isDriverPhoneExist(drivers.getPhone())) {
         throw std::invalid_argument("Phone number already exists!");
     }
     driverDao.createDriver(drivers);
 }

 int64_t DriversService::getDriverById(const int64_t id) const {
     return driverDao.getDriverById(id);
 }

 std::vector<Drivers> DriversService::getAllDrivers() const {
     return driverDao.getAllDrivers();
 }

 void DriversService::updateDriver(const Drivers &drivers) const {
     driverDao.updateDriver(drivers);
 }

 void DriversService::deleteDriver(const int64_t id) const {
     driverDao.deleteDriver(id);
 }

 bool DriversService::isDriverByIdExist(const int64_t id) const {
     return driverDao.isDriverExist(id);
 }

 bool DriversService::isDriverPhoneExist(const std::string &phone) const {
     return driverDao.isPhoneExist(phone);
 }
