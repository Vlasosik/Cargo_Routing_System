#include "factory/RequestHandlerDrivers.h"

#include <Poco/StreamCopier.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include "response/JsonDriversResponse.h"
#include "service/ServiceContainer.h"

using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;

RequestHandlerDrivers::RequestHandlerDrivers() : driversService(ServiceContainer::getInstance().getDriversService()) {
}

void RequestHandlerDrivers::handleRequest(Poco::Net::HTTPServerRequest &request,
                                          Poco::Net::HTTPServerResponse &response) {
    Poco::URI uri(request.getURI());
    auto queryParameters = uri.getQueryParameters();
    response.setContentType("application/json");

    std::unordered_map<std::string, std::function<void()> > methodHandlers = {
        {HTTPRequest::HTTP_POST, [&]() { handleCreateDriver(request, response); }},
        {HTTPRequest::HTTP_GET, [&]() { handleGetDriverById(queryParameters, response); }},
        {HTTPRequest::HTTP_PUT, [&]() { handleUpdateDriver(request, response); }},
        {HTTPRequest::HTTP_DELETE, [&]() { handleDeleteDriver(queryParameters, response); }}
    };

    if (const auto it = methodHandlers.find(request.getMethod()); it != methodHandlers.end()) {
        it->second();
    } else {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        auto &json = response.send();
        JsonDriversResponse::sendJsonErrorMessage(400, "Unsupported HTTP method!", json);
    }
}

void RequestHandlerDrivers::handleCreateDriver(Poco::Net::HTTPServerRequest &request,
                                               Poco::Net::HTTPServerResponse &response) const {
    try {
        if (request.getContentType() != "application/json") {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonDriversResponse::sendJsonErrorMessage(400, "Content-Type must be application/json", json);
            return;
        }
        std::istream &requestBody = request.stream();
        std::ostringstream bodyStream;
        Poco::StreamCopier::copyStream(requestBody, bodyStream);
        std::string body = bodyStream.str();

        Poco::JSON::Parser parser;
        auto jsonObject = parser.parse(body).extract<Poco::JSON::Object::Ptr>();
        if (!jsonObject->has("first_name") || !jsonObject->has("last_name") || !jsonObject->has("phone")) {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonDriversResponse::sendJsonErrorMessage(400, "Missing required fields", json);
            return;
        }
        auto firstName = jsonObject->getValue<std::string>("first_name");
        auto lastName = jsonObject->getValue<std::string>("last_name");
        auto phone = jsonObject->getValue<std::string>("phone");
        Drivers driver(firstName, lastName, phone);
        driversService.createDriver(driver);
        auto &responseStream = response.send();
        JsonDriversResponse::sendJsonSuccessDriversMessage(HTTPResponse::HTTP_CREATED,
                                                           "Driver created successfully", responseStream);
    } catch (const std::exception &ex) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        auto &json = response.send();
        JsonDriversResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                  ex.what(), json);
    }
}

void RequestHandlerDrivers::handleGetDriverById(const Poco::URI::QueryParameters &queryParameters,
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
        JsonDriversResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                  "Missing id query parameter", json);
        return;
    }
    try {
        const int64_t id = std::stol(idValue);
        const auto driverById = driversService.getDriverById(id);
        JsonDriversResponse::sendJsonSuccessByDriversIdMessage(HTTPResponse::HTTP_OK, driverById, json);
    } catch (std::exception &ex) {
        JsonDriversResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST, ex.what(), json);
    }
}

void RequestHandlerDrivers::handleUpdateDriver(Poco::Net::HTTPServerRequest &request,
                                               Poco::Net::HTTPServerResponse &response) const {
    try {
        if (request.getContentType() != "application/json") {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonDriversResponse::sendJsonErrorMessage(400, "Content-Type must be application/json", json);
            return;
        }
        std::istream &requestBody = request.stream();
        std::ostringstream bodyStream;
        Poco::StreamCopier::copyStream(requestBody, bodyStream);
        std::string body = bodyStream.str();

        Poco::JSON::Parser parser;
        auto jsonObject = parser.parse(body).extract<Poco::JSON::Object::Ptr>();
        if (!jsonObject->has("first_name") || !jsonObject->has("last_name") || !jsonObject->has("phone")) {
            response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
            auto &json = response.send();
            JsonDriversResponse::sendJsonErrorMessage(400, "Missing required fields", json);
            return;
        }
        auto id = jsonObject->getValue<long>("id");
        auto firstName = jsonObject->getValue<std::string>("first_name");
        auto lastName = jsonObject->getValue<std::string>("last_name");
        auto phone = jsonObject->getValue<std::string>("phone");
        Drivers driver(id, firstName, lastName, phone);
        driversService.updateDriver(driver);
        auto &responseStream = response.send();
        JsonDriversResponse::sendJsonSuccessDriversMessage(HTTPResponse::HTTP_CREATED,
                                                           "Driver updated successfully", responseStream);
    } catch (const std::exception &ex) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        auto &json = response.send();
        JsonDriversResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                  ex.what(), json);
    }
}

void RequestHandlerDrivers::handleDeleteDriver(const Poco::URI::QueryParameters &queryParameters,
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
        JsonDriversResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST,
                                                  "Missing id query parameter", json);
        return;
    }
    try {
        const int64_t id = std::stol(idValue);
        driversService.deleteDriver(id);
        JsonDriversResponse::sendJsonSuccessDriversMessage(HTTPResponse::HTTP_OK, "Driver successfully deleted!", json);
    } catch (std::exception &ex) {
        JsonDriversResponse::sendJsonErrorMessage(HTTPResponse::HTTP_BAD_REQUEST, ex.what(), json);
    }
}
