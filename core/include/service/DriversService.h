 #ifndef DRIVERSERVICE_H
 #define DRIVERSERVICE_H
 #include "dao/DriverDAO.h"

 class DriversService {
     DriverDAO &driverDao;

 public:
     explicit DriversService(DriverDAO &driverDao);

     void createDriver(const Drivers &drivers) const;

     [[nodiscard]] Drivers getDriverById(int64_t id) const;

     [[nodiscard]] std::vector<Drivers> getAllDrivers() const;

     void updateDriver(const Drivers &drivers) const;

     void deleteDriver(int64_t id) const;

     [[nodiscard]] bool isDriverByIdExist(int64_t id) const;

     [[nodiscard]] bool isDriverPhoneExist(const std::string &phone) const;
 };
 #endif //DRIVERSERVICE_H
