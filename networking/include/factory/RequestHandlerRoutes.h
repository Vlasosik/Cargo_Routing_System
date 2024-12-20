#ifndef REQUESTHANDLERROUTES_H
#define REQUESTHANDLERROUTES_H
#include <Poco/URI.h>
#include <Poco/Net/HTTPRequestHandler.h>

#include "service/RoutesService.h"

class RequestHandlerRoutes : public Poco::Net::HTTPRequestHandler {
    RoutesService &routesService;
public:
    RequestHandlerRoutes();
    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;

    void handleCreateRoute(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) const;

    void handleGetRouteById(const Poco::URI::QueryParameters &queryParameters,
                            Poco::Net::HTTPServerResponse &response) const;

    void handleUpdateRoute(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) const;

    void handleDeleteRoute(const Poco::URI::QueryParameters &queryParameters,
                           Poco::Net::HTTPServerResponse &response) const;
};
#endif //REQUESTHANDLERROUTES_H
