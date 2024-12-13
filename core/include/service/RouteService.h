 #ifndef ROUTESERVICE_H
 #define ROUTESERVICE_H
 #include "dao/RoutesDAO.h"

 class RouteService {
     RoutesDAO &routesDao;

 public:
     explicit RouteService(RoutesDAO &routesDao);

     void createRoute(const Routes &routes) const;

     [[nodiscard]] int64_t getRouteById(int64_t id) const;

     [[nodiscard]] std::vector<Routes> getAllRoutes() const;

     void updateRoute(const Routes &routes) const;

     void deleteRoute(int64_t id) const;

     [[nodiscard]] bool isRouteByIdExist(int64_t id) const;
 };
 #endif //ROUTESERVICE_H
