#ifndef CARGOSERVICE_H
#define CARGOSERVICE_H
#include "dao/CargoesDAO.h"

class CargoesService {
    CargoesDAO &cargoesDao;

public:
    explicit CargoesService(CargoesDAO &cargoesDao);

    void createCargo(const Cargoes &cargoes) const;

    [[nodiscard]] int64_t getCargoById(int64_t id) const;

    [[nodiscard]] std::vector<Cargoes> getAllCargoes() const;

    void updateCargo(const Cargoes &cargoes) const;

    void deleteCargo(int64_t id) const;

    [[nodiscard]] bool isCargoByIdExist(int64_t id) const;
};
#endif //CARGOSERVICE_H
