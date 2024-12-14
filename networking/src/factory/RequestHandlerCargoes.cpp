#include "factory/RequestHandlerCargoes.h"

void RequestHandlerCargoes::handleRequest(Poco::Net::HTTPServerRequest &request,
    Poco::Net::HTTPServerResponse &response) {
    response.setContentType("application/json");
    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    std::ostream& responseStream = response.send();
    responseStream << "{ \"message\": \"Обробник Cargoes відповідає!\" }" << std::endl;
}
