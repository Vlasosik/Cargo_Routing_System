#ifndef REQUESTHANDLERCARGOES_H
#define REQUESTHANDLERCARGOES_H
#include <Poco/URI.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>

#include "RequestHandlerCargoes.h"
#include "service/ServiceContainer.h"

class RequestHandlerCargoes : public Poco::Net::HTTPRequestHandler {
    CargoesService &cargoesService;

public:
    RequestHandlerCargoes();

    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;

    void handleGetCargoById(const Poco::URI::QueryParameters &queryParameters, Poco::Net::HTTPServerResponse &response) const;
    void handlePostCargo(Poco::Net::HTTPServerRequest &request,Poco::Net::HTTPServerResponse &response);
};
#endif //REQUESTHANDLERCARGOES_H
