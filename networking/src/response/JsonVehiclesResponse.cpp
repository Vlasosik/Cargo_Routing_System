#include "response/JsonVehiclesResponse.h"

#include <Poco/JSON/Object.h>

void JsonVehiclesResponse::sendJsonErrorMessage(int errorCode, const std::string &message, std::ostream &json) {
    Poco::JSON::Object responseObject;
    responseObject.set("error_code", errorCode);
    responseObject.set("status", "error");
    responseObject.set("message", message);
    Poco::JSON::Stringifier::stringify(responseObject, json);
}

void JsonVehiclesResponse::sendJsonSuccessByVehiclesIdMessage(int errorCode, const Vehicles &vehicle,
    std::ostream &json) {
    Poco::JSON::Object responseObject;
    responseObject.set("status", "success");
    responseObject.set("error_code", errorCode);
    responseObject.set("message", "Vehicle found");

    Poco::JSON::Object vehicleObject;
    vehicleObject.set("id", vehicle.getId());
    vehicleObject.set("brand", vehicle.getBrand());
    vehicleObject.set("type", vehicle.getType());
    std::string formattedCreatedAt = Vehicles::formatTimeToString(vehicle.getCreatedAt());
    std::string formattedUpdatedAt = Vehicles::formatTimeToString(vehicle.getUpdatedAt());
    vehicleObject.set("createdAt", formattedCreatedAt);
    vehicleObject.set("updatedAt", formattedUpdatedAt);

    responseObject.set("Vehicle Info", vehicleObject);
    std::stringstream jsonStream;
    Poco::JSON::Stringifier::stringify(responseObject, jsonStream);
    json << jsonStream.str();
}

void JsonVehiclesResponse::
sendJsonSuccessVehiclesMessage(int errorCode, const std::string &message, std::ostream &json) {
    Poco::JSON::Object responseObject;
    responseObject.set("error_code", errorCode);
    responseObject.set("status", "success");
    responseObject.set("message", message);
    Poco::JSON::Stringifier::stringify(responseObject, json);
}
