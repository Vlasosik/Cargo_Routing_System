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
    responseObject.set("message", "Route found");

    Poco::JSON::Object routeObject;
    routeObject.set("id", route.getId());
    routeObject.set("driver_id", route.getDriverId());
    routeObject.set("vehicles_id", route.getVehicleId());
    routeObject.set("cargoes_id", route.getCargoesId());
    routeObject.set("start_point", route.getStartPoint());
    routeObject.set("end_point", route.getEndPoint());
    std::string formattedCreatedAt = Routes::formatTimeToString(route.getCreatedAt());
    std::string formattedUpdatedAt = Routes::formatTimeToString(route.getUpdatedAt());
    routeObject.set("created_at", formattedCreatedAt);
    routeObject.set("updated_at", formattedUpdatedAt);

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
