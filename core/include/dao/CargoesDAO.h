#ifndef CARGOESDAO_H
#define CARGOESDAO_H
#include <sqlpp11/postgresql/connection.h>

#include "entity/Cargoes.h"

class CargoesDAO {
    sqlpp::postgresql::connection db;

public:
    CargoesDAO();

    void createCargoes(const TabCargoes &cargoes);

    int64_t getCargoesId(int64_t id);

    std::vector<TabCargoes> getAllCargoes();

    void updateCargoes(const TabCargoes &cargoes);

    void deleteCargoes(int64_t id);

    bool isCargoExist(int64_t id);
};
#endif //CARGOESDAO_H
