 #include "service/CargoesService.h"

 CargoesService::CargoesService(CargoesDAO &cargoesDao): cargoesDao(cargoesDao) {
 }

 void CargoesService::createCargo(const Cargoes &cargoes) const {
     if (cargoes.getWeight() < 0) {
         throw std::invalid_argument("Value must be greater than zero.");
     }
     cargoesDao.createCargoes(cargoes);
 }

 std::vector<Cargoes> CargoesService::getAllCargoes() const {
     return cargoesDao.getAllCargoes();
 }

 Cargoes CargoesService::getCargoById(const int64_t id) const {
     return cargoesDao.getCargoesById(id);
 }

 void CargoesService::updateCargo(const Cargoes &cargoes) const {
     cargoesDao.updateCargoes(cargoes);
 }

 void CargoesService::deleteCargo(const int64_t id) const {
     cargoesDao.deleteCargoes(id);
 }

 bool CargoesService::isCargoByIdExist(const int64_t id) const {
     return cargoesDao.isCargoExist(id);
 }
