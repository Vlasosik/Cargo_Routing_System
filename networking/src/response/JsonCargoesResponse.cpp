#include "response/JsonCargoesResponse.h"

#include <Poco/JSON/Object.h>

void JsonCargoesResponse::sendJsonErrorMessage(const int errorCode, const std::string &message, std::ostream &json) {
    Poco::JSON::Object responseObject;
    responseObject.set("error_code", errorCode);
    responseObject.set("status", "error");
    responseObject.set("message", message);
    Poco::JSON::Stringifier::stringify(responseObject, json);
}

void JsonCargoesResponse::sendJsonSuccessByCargoesIdMessage(const int errorCode, const Cargoes &cargo,
                                                            std::ostream &json) {
    Poco::JSON::Object responseObject;
    responseObject.set("status", "success");
    responseObject.set("error_code", errorCode);
    responseObject.set("message", "Cargo found");

    Poco::JSON::Object cargoObject;
    cargoObject.set("id", cargo.getId());
    cargoObject.set("name", cargo.getName());
    cargoObject.set("weight", cargo.getWeight());
    cargoObject.set("sender", cargo.getSender());
    cargoObject.set("receipt", cargo.getReceipt());
    std::string formattedCreatedAt = Cargoes::formatTimeToString(cargo.getCreatedAt());
    std::string formattedUpdatedAt = Cargoes::formatTimeToString(cargo.getUpdatedAt());
    cargoObject.set("createdAt", formattedCreatedAt);
    cargoObject.set("updatedAt", formattedUpdatedAt);

    responseObject.set("Cargo Info", cargoObject);
    std::stringstream jsonStream;
    Poco::JSON::Stringifier::stringify(responseObject, jsonStream);
    json << jsonStream.str();
}

void JsonCargoesResponse::sendJsonSuccessCargoesMessage(int errorCode, const std::string &message,
                                                        std::ostream &json) {
    Poco::JSON::Object responseObject;
    responseObject.set("error_code", errorCode);
    responseObject.set("status", "success");
    responseObject.set("message", message);
    Poco::JSON::Stringifier::stringify(responseObject, json);
}
