#ifndef JSONROUTESRESPONSE_H
#define JSONROUTESRESPONSE_H

#include <Poco/JSON/Object.h>

#include "dao/RoutesDAO.h"

class JsonRoutesResponse {
public:
    static void sendJsonErrorMessage(int errorCode, const std::string &message, std::ostream &json);

    static void sendJsonSuccessByRouteIdMessage(int errorCode, const Routes &route, std::ostream &json);

    static void sendJsonSuccessRouteMessage(int errorCode, const std::string &message, std::ostream &json);
};
#endif //JSONROUTESRESPONSE_H
