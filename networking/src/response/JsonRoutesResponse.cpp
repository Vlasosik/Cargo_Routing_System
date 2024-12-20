#include "response/JsonRoutesResponse.h"

void JsonRoutesResponse::sendJsonErrorMessage(int errorCode, const std::string &message, std::ostream &json) {
    Poco::JSON::Object responseObject;
    responseObject.set("error_code", errorCode);
    responseObject.set("status", "error");
    responseObject.set("message", message);
    Poco::JSON::Stringifier::stringify(responseObject, json);
}

void JsonRoutesResponse::sendJsonSuccessByRouteIdMessage(int errorCode, const Routes &route, std::ostream &json) {
    Poco::JSON::Object responseObject;
    responseObject.set("status", "success");
    responseObject.set("error_code", errorCode);
    responseObject.set("message", "Cargo found");

    Poco::JSON::Object routeObject;
    routeObject.set("id", route.getId());
    routeObject.set("driverId", route.getDriverId());
    routeObject.set("vehiclesId", route.getVehicleId());
    routeObject.set("cargoesId", route.getCargoesId());
    routeObject.set("startPoint", route.getStartPoint());
    routeObject.set("endPoint", route.getEndPoint());
    std::string formattedCreatedAt = Routes::formatTimeToString(route.getCreatedAt());
    std::string formattedUpdatedAt = Routes::formatTimeToString(route.getUpdatedAt());
    routeObject.set("createdAt", formattedCreatedAt);
    routeObject.set("updatedAt", formattedUpdatedAt);

    responseObject.set("Route Info", routeObject);
    std::stringstream jsonStream;
    Poco::JSON::Stringifier::stringify(responseObject, jsonStream);
    json << jsonStream.str();
}

void JsonRoutesResponse::sendJsonSuccessRouteMessage(int errorCode, const std::string &message, std::ostream &json) {
    Poco::JSON::Object responseObject;
    responseObject.set("error_code", errorCode);
    responseObject.set("status", "success");
    responseObject.set("message", message);
    Poco::JSON::Stringifier::stringify(responseObject, json);
}
