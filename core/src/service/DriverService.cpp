 #include "service/DriverService.h"

 DriverService::DriverService(DriverDAO &driverDao) : driverDao(driverDao) {
 }

 void DriverService::createDriver(const Drivers &drivers) const {
     if (drivers.getId() <= 0) {
         throw std::invalid_argument("Id must be greater than zero.");
     }
     if (isDriverPhoneExist(drivers.getPhone())) {
         throw std::invalid_argument("Phone number already exists!");
     }
     driverDao.createDriver(drivers);
 }

 int64_t DriverService::getDriverById(const int64_t id) const {
     return driverDao.getDriverById(id);
 }

 std::vector<Drivers> DriverService::getAllDrivers() const {
     return driverDao.getAllDrivers();
 }

 void DriverService::updateDriver(const Drivers &drivers) const {
     driverDao.updateDriver(drivers);
 }

 void DriverService::deleteDriver(const int64_t id) const {
     driverDao.deleteDriver(id);
 }

 bool DriverService::isDriverByIdExist(const int64_t id) const {
     return driverDao.isDriverExist(id);
 }

 bool DriverService::isDriverPhoneExist(const std::string &phone) const {
     return driverDao.isPhoneExist(phone);
 }
