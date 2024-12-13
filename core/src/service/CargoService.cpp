 #include "service/CargoService.h"

 CargoService::CargoService(CargoesDAO &cargoesDao): cargoesDao(cargoesDao) {
 }

 void CargoService::createCargo(const Cargoes &cargoes) const {
     if (cargoes.getId() <= 0) {
         throw std::invalid_argument("Id must be greater than zero.");
     }
     cargoesDao.createCargoes(cargoes);
 }

 int64_t CargoService::getCargoById(const int64_t id) const {
     return cargoesDao.getCargoesById(id);
 }

 std::vector<Cargoes> CargoService::getAllCargoes() const {
     return cargoesDao.getAllCargoes();
 }

 void CargoService::updateCargo(const Cargoes &cargoes) const {
     cargoesDao.updateCargoes(cargoes);
 }

 void CargoService::deleteCargo(const int64_t id) const {
     cargoesDao.deleteCargoes(id);
 }

 bool CargoService::isCargoByIdExist(const int64_t id) const {
     return cargoesDao.isCargoExist(id);
 }
