  #include "service/RoutesService.h"

  RoutesService::RoutesService(RoutesDAO &routesDao) : routesDao(routesDao) {
  }

  void RoutesService::createRoute(const Routes &routes) const {
      routesDao.createRoutes(routes);
  }

  Routes RoutesService::getRouteById(const int64_t id) const {
      return routesDao.getRoutesById(id);
  }

  std::vector<Routes> RoutesService::getAllRoutes() const {
      return routesDao.getAllRoutes();
  }

  void RoutesService::updateRoute(const Routes &routes) const {
      routesDao.updateRoutes(routes);
  }

  void RoutesService::deleteRoute(const int64_t id) const {
      routesDao.deleteRoutes(id);
  }

  bool RoutesService::isRouteByIdExist(const int64_t id) const {
      return routesDao.isRoutesExist(id);
  }
