#include "factory/RequestHandlerCargoes.h"

#include <Poco/URI.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/JSON/Parser.h>

#include "http_server/HttpServer.h"
#include "response/JsonCargoesResponse.h"

using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;

RequestHandlerCargoes::RequestHandlerCargoes() : cargoesService(ServiceContainer::getInstance().getCargoesService()) {
}

void RequestHandlerCargoes::handleRequest(Poco::Net::HTTPServerRequest &request,
                                          Poco::Net::HTTPServerResponse &response) {
    const Poco::URI uri(request.getURI());
    auto queryParameters = uri.getQueryParameters();
    response.setContentType("application/json");

    std::unordered_map<std::string, std::function<void()> > methodHandlers = {
        {HTTPRequest::HTTP_POST, [&]() { handleCreateCargo(request, response); }},
        {HTTPRequest::HTTP_GET, [&]() { handleGetCargoById(queryParameters, response); }},
        {HTTPRequest::HTTP_PUT, [&]() { handleUpdateCargo(request, response); }},
        {HTTPRequest::HTTP_DELETE, [&]() { handleDeleteCargo(queryParameters, response); }}
    };

    if (const auto it = methodHandlers.find(request.getMethod()); it != methodHandlers.end()) {
        it->second();
    } else {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        auto &json = response.send();
        JsonCargoesResponse::sendJsonErrorMessage(400, "Unsupported HTTP method!", json);
    }
}

void RequestHandlerCargoes::handleCreateCargo(Poco::Net::HTTPServerRequest &request,
                                              Poco::Net::HTTPServerResponse &response) const {
    try {
        if (request.getContentType() != "application/json") {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonCargoesResponse::sendJsonErrorMessage(400, "Content-Type must be application/json", json);
            return;
        }
        std::istream &requestBody = request.stream();
        std::ostringstream bodyStream;
        Poco::StreamCopier::copyStream(requestBody, bodyStream);
        std::string body = bodyStream.str();

        Poco::JSON::Parser parser;
        auto jsonObject = parser.parse(body).extract<Poco::JSON::Object::Ptr>();
        if (!jsonObject->has("name") || !jsonObject->has("weight") || !jsonObject->has("sender")
            || !jsonObject->has("receipt")) {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonCargoesResponse::sendJsonErrorMessage(400, "Missing required fields", json);
            return;
        }
        auto name = jsonObject->getValue<std::string>("name");
        auto weight = jsonObject->getValue<double>("weight");
        auto sender = jsonObject->getValue<std::string>("sender");
        auto receipt = jsonObject->getValue<std::string>("receipt");
        Cargoes cargo(name, weight, sender, receipt);
        cargoesService.createCargo(cargo);
        auto &responseStream = response.send();
        JsonCargoesResponse::sendJsonSuccessCargoesMessage(HTTPResponse::HTTP_CREATED,
                                                           "Cargo created successfully", responseStream);
    } catch (const std::exception &ex) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        auto &json = response.send();
        JsonCargoesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                  ex.what(), json);
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
        JsonCargoesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                  "Missing id query parameter", json);
        return;
    }
    try {
        const int64_t id = std::stol(idValue);
        const auto cargoById = cargoesService.getCargoById(id);
        JsonCargoesResponse::sendJsonSuccessByCargoesIdMessage(HTTPResponse::HTTP_OK, cargoById, json);
    } catch (std::exception &ex) {
        JsonCargoesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST, ex.what(), json);
    }
}

void RequestHandlerCargoes::handleUpdateCargo(Poco::Net::HTTPServerRequest &request,
                                              Poco::Net::HTTPServerResponse &response) const {
    try {
        if (request.getContentType() != "application/json") {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonCargoesResponse::sendJsonErrorMessage(400, "Content-Type must be application/json", json);
            return;
        }
        std::istream &requestBody = request.stream();
        std::ostringstream bodyStream;
        Poco::StreamCopier::copyStream(requestBody, bodyStream);
        std::string body = bodyStream.str();

        Poco::JSON::Parser parser;
        auto jsonObject = parser.parse(body).extract<Poco::JSON::Object::Ptr>();
        if (!jsonObject->has("name") || !jsonObject->has("weight") || !jsonObject->has("sender")
            || !jsonObject->has("receipt")) {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonCargoesResponse::sendJsonErrorMessage(400, "Missing required fields", json);
            return;
        }
        auto id = jsonObject->getValue<long>("id");
        auto name = jsonObject->getValue<std::string>("name");
        auto weight = jsonObject->getValue<double>("weight");
        auto sender = jsonObject->getValue<std::string>("sender");
        auto receipt = jsonObject->getValue<std::string>("receipt");
        Cargoes cargo(id, name, weight, sender, receipt);
        cargoesService.updateCargo(cargo);
        auto &responseStream = response.send();
        JsonCargoesResponse::sendJsonSuccessCargoesMessage(HTTPResponse::HTTP_CREATED,
                                                           "Cargo updated successfully", responseStream);
    } catch (const std::exception &ex) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        auto &json = response.send();
        JsonCargoesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                  ex.what(), json);
    }
}

void RequestHandlerCargoes::handleDeleteCargo(const Poco::URI::QueryParameters &queryParameters,
                                              Poco::Net::HTTPServerResponse &response) const {
    auto &json = response.send();
    std::string idValue;
    for (const auto &[key, value]: queryParameters) {
        if (key == "id") {
            idValue = value;
            break;
        }
    }
    if (idValue.empty()) {
        JsonCargoesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                  "Missing id query parameter", json);
        return;
    }
    try {
        const int64_t id = std::stol(idValue);
        cargoesService.deleteCargo(id);
        JsonCargoesResponse::sendJsonSuccessCargoesMessage(HTTPResponse::HTTP_OK,
                                                           "Cargo successfully deleted!", json);
    } catch (std::exception &ex) {
        JsonCargoesResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST, ex.what(), json);
    }
}
