  #include "service/RouteService.h"

  RouteService::RouteService(RoutesDAO &routesDao) : routesDao(routesDao) {
  }

  void RouteService::createRoute(const Routes &routes) const {
      if (routes.id <= 0) {
          throw std::invalid_argument("Id must be greater than zero.");
      }
      routesDao.createRoutes(routes);
  }

  int64_t RouteService::getRouteById(const int64_t id) const {
      return routesDao.getRoutesById(id);
  }

  std::vector<Routes> RouteService::getAllRoutes() const {
      return routesDao.getAllRoutes();
  }

  void RouteService::updateRoute(const Routes &routes) const {
      routesDao.updateRoutes(routes);
  }

  void RouteService::deleteRoute(const int64_t id) const {
      routesDao.deleteRoutes(id);
  }

  bool RouteService::isRouteByIdExist(const int64_t id) const {
      return routesDao.isRoutesExist(id);
  }
