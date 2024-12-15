#ifndef JSONCARGOESRESPONSE_H
#define JSONCARGOESRESPONSE_H
#include "entity/Cargoes.h"

class JsonCargoesResponse {
public:
    static void sendJsonErrorMessage(int errorCode, const std::string &message, std::ostream &json);
    static void sendJsonSuccessByCargoesIdMessage(const Cargoes &cargo, std::ostream &json);
};
#endif //JSONCARGOESRESPONSE_H
