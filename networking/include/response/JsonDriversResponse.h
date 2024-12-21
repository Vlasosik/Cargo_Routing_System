#ifndef JSONDRIVERSRESPONSE_H
#define JSONDRIVERSRESPONSE_H
#include "dao/DriverDAO.h"

class JsonDriversResponse {
public:
    static void sendJsonErrorMessage(int errorCode, const std::string &message, std::ostream &json);

    static void sendJsonSuccessByDriversIdMessage(int errorCode, const Drivers &drivers, std::ostream &json);

    static void sendJsonSuccessDriversMessage(int errorCode, const std::string &message, std::ostream &json);
};
#endif //JSONDRIVERSRESPONSE_H
