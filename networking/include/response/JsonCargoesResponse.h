#ifndef JSONCARGOESRESPONSE_H
#define JSONCARGOESRESPONSE_H

#include "dao/CargoesDAO.h"

class JsonCargoesResponse {
public:
    static void sendJsonErrorMessage(int errorCode, const std::string &message, std::ostream &json);

    static void sendJsonSuccessByCargoesIdMessage(int errorCode, const Cargoes &cargo, std::ostream &json);

    static void sendJsonSuccessCargoesMessage(int errorCode, const std::string &message, std::ostream &json);
};
#endif //JSONCARGOESRESPONSE_H
