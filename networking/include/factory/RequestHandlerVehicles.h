#ifndef REQUESTHANDLERVEHICLES_H
#define REQUESTHANDLERVEHICLES_H
#include <Poco/URI.h>
#include <Poco/Net/HTTPRequestHandler.h>

#include "service/VehiclesService.h"

class RequestHandlerVehicles : public Poco::Net::HTTPRequestHandler {
    VehiclesService &vehiclesService;

public:
    RequestHandlerVehicles();

    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;

    void handleCreateVehicle(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) const;

    void handleGetVehicleById(const Poco::URI::QueryParameters &queryParameters,
                             Poco::Net::HTTPServerResponse &response) const;

    void handleUpdateVehicle(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) const;

    void handleDeleteVehicle(const Poco::URI::QueryParameters &queryParameters,
                            Poco::Net::HTTPServerResponse &response) const;
};
#endif //REQUESTHANDLERVEHICLES_H
