#include "factory/RequestHandlerRoutes.h"

#include <Poco/StreamCopier.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include "response/JsonRoutesResponse.h"
#include "service/ServiceContainer.h"

using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;

RequestHandlerRoutes::RequestHandlerRoutes() : routesService(ServiceContainer::getInstance().getRoutesService()) {
}

void RequestHandlerRoutes::
handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    const Poco::URI uri(request.getURI());
    auto queryParameters = uri.getQueryParameters();
    response.setContentType("application/json");

    std::unordered_map<std::string, std::function<void()> > methodHandlers = {
        {HTTPRequest::HTTP_POST, [&]() { handleCreateRoute(request, response); }},
        {HTTPRequest::HTTP_GET, [&]() { handleGetRouteById(queryParameters, response); }},
        {HTTPRequest::HTTP_PUT, [&]() { handleUpdateRoute(request, response); }},
        {HTTPRequest::HTTP_DELETE, [&]() { handleDeleteRoute(queryParameters, response); }}
    };

    if (const auto it = methodHandlers.find(request.getMethod()); it != methodHandlers.end()) {
        it->second();
    } else {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        auto &json = response.send();
        JsonRoutesResponse::sendJsonErrorMessage(400, "Unsupported HTTP method!", json);
    }
}

void RequestHandlerRoutes::handleCreateRoute(Poco::Net::HTTPServerRequest &request,
                                             Poco::Net::HTTPServerResponse &response) const {
    try {
        if (request.getContentType() != "application/json") {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonRoutesResponse::sendJsonErrorMessage(400, "Content-Type must be application/json", json);
            return;
        }
        std::istream &requestBody = request.stream();
        std::ostringstream bodyStream;
        Poco::StreamCopier::copyStream(requestBody, bodyStream);
        std::string body = bodyStream.str();

        Poco::JSON::Parser parser;
        auto jsonObject = parser.parse(body).extract<Poco::JSON::Object::Ptr>();
        if (!jsonObject->has("driver_id") || !jsonObject->has("vehicles_id") || !jsonObject->has("cargoes_id")
            || !jsonObject->has("start_point") || !jsonObject->has("end_point") || !jsonObject->has("status")) {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonRoutesResponse::sendJsonErrorMessage(400, "Missing required fields", json);
            return;
        }
        auto driverId = jsonObject->getValue<long>("driver_id");
        auto vehiclesId = jsonObject->getValue<long>("vehicles_id");
        auto cargoesId = jsonObject->getValue<long>("cargoes_id");
        auto startPoint = jsonObject->getValue<std::string>("start_point");
        auto endPoint = jsonObject->getValue<std::string>("end_point");
        auto status = jsonObject->getValue<std::string>("status");
        Routes route(driverId, vehiclesId, cargoesId, startPoint, endPoint, status);
        routesService.createRoute(route);
        auto &responseStream = response.send();
        JsonRoutesResponse::sendJsonSuccessRouteMessage(HTTPResponse::HTTP_CREATED, "Route created successfully",
                                                        responseStream);
    } catch (const std::exception &ex) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        auto &json = response.send();
        JsonRoutesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                 ex.what(), json);
    }
}

void RequestHandlerRoutes::handleGetRouteById(const Poco::URI::QueryParameters &queryParameters,
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
        JsonRoutesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                 "Missing id query parameter", json);
        return;
    }
    try {
        const int64_t id = std::stol(idValue);
        const auto routeById = routesService.getRouteById(id);
        JsonRoutesResponse::sendJsonSuccessByRouteIdMessage(HTTPResponse::HTTP_OK, routeById, json);
    } catch (std::exception &ex) {
        JsonRoutesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST, ex.what(), json);
    }
}

void RequestHandlerRoutes::handleUpdateRoute(Poco::Net::HTTPServerRequest &request,
                                             Poco::Net::HTTPServerResponse &response) const {
    try {
        if (request.getContentType() != "application/json") {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonRoutesResponse::sendJsonErrorMessage(400, "Content-Type must be application/json", json);
            return;
        }
        std::istream &requestBody = request.stream();
        std::ostringstream bodyStream;
        Poco::StreamCopier::copyStream(requestBody, bodyStream);
        std::string body = bodyStream.str();

        Poco::JSON::Parser parser;
        auto jsonObject = parser.parse(body).extract<Poco::JSON::Object::Ptr>();
        if (!jsonObject->has("driver_id") || !jsonObject->has("vehicles_id") || !jsonObject->has("cargoes_id")
            || !jsonObject->has("start_point") || !jsonObject->has("end_point") || !jsonObject->has("status")) {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonRoutesResponse::sendJsonErrorMessage(400, "Missing required fields", json);
            return;
        }
        auto id = jsonObject->getValue<long>("id");
        auto driverId = jsonObject->getValue<long>("driver_id");
        auto vehiclesId = jsonObject->getValue<long>("vehicles_id");
        auto cargoesId = jsonObject->getValue<long>("cargoes_id");
        auto startPoint = jsonObject->getValue<std::string>("start_point");
        auto endPoint = jsonObject->getValue<std::string>("end_point");
        auto status = jsonObject->getValue<std::string>("status");
        Routes route(id, driverId, vehiclesId, cargoesId, startPoint, endPoint, status);
        routesService.updateRoute(route);
        auto &responseStream = response.send();
        JsonRoutesResponse::sendJsonSuccessRouteMessage(HTTPResponse::HTTP_CREATED, "Route updated successfully",
                                                        responseStream);
    } catch (const std::exception &ex) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        auto &json = response.send();
        JsonRoutesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                 ex.what(), json);
    }
}

void RequestHandlerRoutes::handleDeleteRoute(const Poco::URI::QueryParameters &queryParameters,
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
        JsonRoutesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                 "Missing id query parameter", json);
        return;
    }
    try {
        const int64_t id = std::stol(idValue);
        routesService.deleteRoute(id);
        JsonRoutesResponse::sendJsonSuccessRouteMessage(HTTPResponse::HTTP_OK, "Cargo successfully deleted!", json);
    } catch (std::exception &ex) {
        JsonRoutesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST, ex.what(), json);
    }
}
