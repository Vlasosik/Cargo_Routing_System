#include "factory/RequestHandlerCargoes.h"

#include <Poco/URI.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

RequestHandlerCargoes::RequestHandlerCargoes() : cargoesService(ServiceContainer::getInstance().getCargoesService()) {
}

void RequestHandlerCargoes::handleRequest(Poco::Net::HTTPServerRequest &request,
                                          Poco::Net::HTTPServerResponse &response) {
    const Poco::URI uri(request.getURI());
    Poco::URI::QueryParameters queryParameters = uri.getQueryParameters();
    response.setContentType("application/json");
    if (request.getMethod() == "GET") {
        handleGetCargoById(queryParameters, response);
    }
}

void RequestHandlerCargoes::handleGetCargoById(const Poco::URI::QueryParameters &queryParameters,
                                               Poco::Net::HTTPServerResponse &response) const {
    std::ostream &json = response.send();
    std::string idValue;
    for (const auto &[key, value]: queryParameters) {
        if (key == "id") {
            idValue = value;
            break;
        }
    }
    if (idValue.empty()) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
        json << R"({"status": "error", "error_code": 400, "message": "Missing id query parameter"})";
        return;
    }
    try {
        const int64_t id = std::stol(idValue);
        const auto cargoById = cargoesService.getCargoById(id);
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        Poco::JSON::Object responseObject;
        responseObject.set("status", "success");
        responseObject.set("error_code", 200);
        responseObject.set("message", "Cargo found");

        Poco::JSON::Object cargoObject;
        cargoObject.set("id", cargoById.getId());
        cargoObject.set("name", cargoById.getName());
        cargoObject.set("weight", cargoById.getWeight());
        cargoObject.set("sender", cargoById.getSender());
        cargoObject.set("receipt", cargoById.getReceipt());

        std::string formattedCreatedAt = Cargoes::formatTimeToString(cargoById.getCreatedAt());
        std::string formattedUpdatedAt = Cargoes::formatTimeToString(cargoById.getUpdatedAt());
        cargoObject.set("createdAt", formattedCreatedAt);
        cargoObject.set("updatedAt", formattedUpdatedAt);

        responseObject.set("Cargo Info", cargoObject);

        std::stringstream jsonStream;
        responseObject.stringify(jsonStream);

        json << jsonStream.str();
    } catch (std::exception &ex) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
        json << R"({"status": "error", "error_code": 403, "message": "Cargo doesn’t exist!"})";
    }
}
