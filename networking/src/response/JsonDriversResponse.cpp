#include "response/JsonDriversResponse.h"

#include <Poco/JSON/Object.h>

void JsonDriversResponse::sendJsonErrorMessage(int errorCode, const std::string &message, std::ostream &json) {
    Poco::JSON::Object responseObject;
    responseObject.set("error_code", errorCode);
    responseObject.set("status", "error");
    responseObject.set("message", message);
    Poco::JSON::Stringifier::stringify(responseObject, json);
}

void JsonDriversResponse::sendJsonSuccessByDriversIdMessage(int errorCode, const Drivers &drivers, std::ostream &json) {
    Poco::JSON::Object responseObject;
    responseObject.set("status", "success");
    responseObject.set("error_code", errorCode);
    responseObject.set("message", "Driver found");

    Poco::JSON::Object driverObject;
    driverObject.set("id", drivers.getId());
    driverObject.set("first_name", drivers.getFirstName());
    driverObject.set("last_name", drivers.getLastName());
    driverObject.set("phone", drivers.getPhone());
    std::string formattedCreatedAt = Drivers::formatTimeToString(drivers.getCreatedAt());
    std::string formattedUpdatedAt = Drivers::formatTimeToString(drivers.getUpdatedAt());
    driverObject.set("created_at", formattedCreatedAt);
    driverObject.set("updated_at", formattedUpdatedAt);

    responseObject.set("Driver Info", driverObject);
    std::stringstream jsonStream;
    Poco::JSON::Stringifier::stringify(responseObject, jsonStream);
    json << jsonStream.str();
}

void JsonDriversResponse::sendJsonSuccessDriversMessage(int errorCode, const std::string &message, std::ostream &json) {
    Poco::JSON::Object responseObject;
    responseObject.set("error_code", errorCode);
    responseObject.set("status", "success");
    responseObject.set("message", message);
    Poco::JSON::Stringifier::stringify(responseObject, json);
}
