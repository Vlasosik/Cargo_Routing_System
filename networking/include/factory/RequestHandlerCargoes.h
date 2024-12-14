#ifndef REQUESTHANDLERCARGOES_H
#define REQUESTHANDLERCARGOES_H
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerResponse.h>

#include "RequestHandlerCargoes.h"

class RequestHandlerCargoes : public Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
};
#endif //REQUESTHANDLERCARGOES_H
