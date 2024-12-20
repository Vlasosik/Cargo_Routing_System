#ifndef ROUTESDAO_H
#define ROUTESDAO_H
#include <sqlpp11/postgresql/postgresql.h>

#include "entity/Routes.h"

class RoutesDAO {
    sqlpp::postgresql::connection db;

public:
    RoutesDAO();

    void createRoutes(const Routes &routes);

    Routes getRoutesById(const int64_t &id);

    std::vector<Routes> getAllRoutes();

    void updateRoutes(const Routes &routes);

    void deleteRoutes(const int64_t &id);

    bool isRoutesExist(const int64_t &id);
};
#endif //ROUTESDAO_H
