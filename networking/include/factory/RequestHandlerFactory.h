#ifndef REQUESTHANDLERFACTORY_H
#define REQUESTHANDLERFACTORY_H
#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include "RequestHandlerCargoes.h"
#include "RequestHandlerRoutes.h"

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
    std::unordered_map<std::string, std::function<Poco::Net::HTTPRequestHandler*()> > handler;

    void registerHandler(const std::string &path, const std::function<Poco::Net::HTTPRequestHandler*()> &creator) {
        handler[path] = creator;
    }
public:
    RequestHandlerFactory();

    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override;
};
#endif //REQUESTHANDLERFACTORY_H
