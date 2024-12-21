#ifndef JSONVEHICLESRESPONSE_H
#define JSONVEHICLESRESPONSE_H
#include "dao/VehiclesDAO.h"

class JsonVehiclesResponse {
public:
    static void sendJsonErrorMessage(int errorCode, const std::string &message, std::ostream &json);

    static void sendJsonSuccessByVehiclesIdMessage(int errorCode, const Vehicles &vehicle, std::ostream &json);

    static void sendJsonSuccessVehiclesMessage(int errorCode, const std::string &message, std::ostream &json);
};
#endif //JSONVEHICLESRESPONSE_H
