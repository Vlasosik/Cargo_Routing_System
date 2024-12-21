#ifndef REQUESTHANDLERDRIVERS_H
#define REQUESTHANDLERDRIVERS_H
#include <Poco/URI.h>
#include <Poco/Net/HTTPRequestHandler.h>

#include "service/DriversService.h"

class RequestHandlerDrivers : public Poco::Net::HTTPRequestHandler {
    DriversService &driversService;
public:
    RequestHandlerDrivers();

    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;

    void handleCreateDriver(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) const;

    void handleGetDriverById(const Poco::URI::QueryParameters &queryParameters,
                             Poco::Net::HTTPServerResponse &response) const;

    void handleUpdateDriver(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) const;

    void handleDeleteDriver(const Poco::URI::QueryParameters &queryParameters,
                            Poco::Net::HTTPServerResponse &response) const;
};
#endif //REQUESTHANDLERDRIVERS_H
