  #include "service/RoutesService.h"

  RoutesService::RoutesService(RoutesDAO &routesDao) : routesDao(routesDao) {
  }

  void RoutesService::createRoute(const Routes &routes) const {
      if (routes.id <= 0) {
          throw std::invalid_argument("Id must be greater than zero.");
      }
      routesDao.createRoutes(routes);
  }

  int64_t RoutesService::getRouteById(const int64_t id) const {
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
