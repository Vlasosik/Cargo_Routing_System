 #ifndef VEHICLESERVICE_H
 #define VEHICLESERVICE_H
 #include "dao/VehiclesDAO.h"

 class VehiclesService {
     VehiclesDAO &vehiclesDao;
 public:
     explicit VehiclesService(VehiclesDAO &vehiclesDao);

     void createVehicle(const Vehicles &vehicles) const;

     [[nodiscard]] Vehicles getVehicleById(int64_t id) const;

     [[nodiscard]] std::vector<Vehicles> getAllVehicles() const;

     void updateVehicle(const Vehicles &vehicles) const;

     void deleteVehicle(int64_t id) const;

     [[nodiscard]] bool isVehicleByIdExist(int64_t id) const;
 };
 #endif //VEHICLESERVICE_H
