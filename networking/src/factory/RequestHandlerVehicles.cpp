#include "factory/RequestHandlerVehicles.h"

#include <Poco/StreamCopier.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include "response/JsonCargoesResponse.h"
#include "response/JsonVehiclesResponse.h"
#include "service/ServiceContainer.h"

using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;

RequestHandlerVehicles::RequestHandlerVehicles() : vehiclesService(
    ServiceContainer::getInstance().getVehiclesService()) {
}

void RequestHandlerVehicles::handleRequest(Poco::Net::HTTPServerRequest &request,
                                           Poco::Net::HTTPServerResponse &response) {
    const Poco::URI uri(request.getURI());
    auto queryParameters = uri.getQueryParameters();
    response.setContentType("application/json");

    std::unordered_map<std::string, std::function<void()> > methodHandlers = {
        {HTTPRequest::HTTP_POST, [&]() { handleCreateVehicle(request, response); }},
        {HTTPRequest::HTTP_GET, [&]() { handleGetVehicleById(queryParameters, response); }},
        {HTTPRequest::HTTP_PUT, [&]() { handleUpdateVehicle(request, response); }},
        {HTTPRequest::HTTP_DELETE, [&]() { handleDeleteVehicle(queryParameters, response); }}
    };

    if (const auto it = methodHandlers.find(request.getMethod()); it != methodHandlers.end()) {
        it->second();
    } else {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        auto &json = response.send();
        JsonVehiclesResponse::sendJsonErrorMessage(400, "Unsupported HTTP method!", json);
    }
}

void RequestHandlerVehicles::handleCreateVehicle(Poco::Net::HTTPServerRequest &request,
                                                 Poco::Net::HTTPServerResponse &response) const {
    try {
        if (request.getContentType() != "application/json") {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonVehiclesResponse::sendJsonErrorMessage(400, "Content-Type must be application/json", json);
            return;
        }
        std::istream &requestBody = request.stream();
        std::ostringstream bodyStream;
        Poco::StreamCopier::copyStream(requestBody, bodyStream);
        std::string body = bodyStream.str();

        Poco::JSON::Parser parser;
        auto jsonObject = parser.parse(body).extract<Poco::JSON::Object::Ptr>();
        if (!jsonObject->has("brand") || !jsonObject->has("type")) {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonVehiclesResponse::sendJsonErrorMessage(400, "Missing required fields", json);
            return;
        }
        auto brand = jsonObject->getValue<std::string>("brand");
        auto type = jsonObject->getValue<std::string>("type");
        Vehicles vehicle(brand, type);
        vehiclesService.createVehicle(vehicle);
        auto &responseStream = response.send();
        JsonCargoesResponse::sendJsonSuccessCargoesMessage(HTTPResponse::HTTP_CREATED,
                                                           "Cargo created successfully", responseStream);
    } catch (const std::exception &ex) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        auto &json = response.send();
        JsonVehiclesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                   ex.what(), json);
    }
}

void RequestHandlerVehicles::handleGetVehicleById(const Poco::URI::QueryParameters &queryParameters,
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
        JsonVehiclesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                   "Missing id query parameter", json);
        return;
    }
    try {
        const int64_t id = std::stol(idValue);
        const auto vehicleById = vehiclesService.getVehicleById(id);
        JsonVehiclesResponse::sendJsonSuccessByVehiclesIdMessage(HTTPResponse::HTTP_OK, vehicleById, json);
    } catch (std::exception &ex) {
        JsonVehiclesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST, ex.what(), json);
    }
}

void RequestHandlerVehicles::handleUpdateVehicle(Poco::Net::HTTPServerRequest &request,
                                                 Poco::Net::HTTPServerResponse &response) const {
    try {
        if (request.getContentType() != "application/json") {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonVehiclesResponse::sendJsonErrorMessage(400, "Content-Type must be application/json", json);
            return;
        }
        std::istream &requestBody = request.stream();
        std::ostringstream bodyStream;
        Poco::StreamCopier::copyStream(requestBody, bodyStream);
        std::string body = bodyStream.str();

        Poco::JSON::Parser parser;
        auto jsonObject = parser.parse(body).extract<Poco::JSON::Object::Ptr>();
        if (!jsonObject->has("brand") || !jsonObject->has("type")) {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonVehiclesResponse::sendJsonErrorMessage(400, "Missing required fields", json);
            return;
        }
        auto id = jsonObject->getValue<long>("id");
        auto brand = jsonObject->getValue<std::string>("brand");
        auto type = jsonObject->getValue<std::string>("type");
        Vehicles vehicle(id, brand, type);
        vehiclesService.updateVehicle(vehicle);
        auto &responseStream = response.send();
        JsonCargoesResponse::sendJsonSuccessCargoesMessage(HTTPResponse::HTTP_CREATED,
                                                           "Cargo updated successfully", responseStream);
    } catch (const std::exception &ex) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        auto &json = response.send();
        JsonVehiclesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                   ex.what(), json);
    }
}

void RequestHandlerVehicles::handleDeleteVehicle(const Poco::URI::QueryParameters &queryParameters,
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
        JsonVehiclesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                   "Missing id query parameter", json);
        return;
    }
    try {
        const int64_t id = std::stol(idValue);
        vehiclesService.deleteVehicle(id);
        JsonVehiclesResponse::sendJsonSuccessVehiclesMessage(HTTPResponse::HTTP_OK, "Cargo deleted successfully", json);
    } catch (std::exception &ex) {
        JsonVehiclesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST, ex.what(), json);
    }
}
