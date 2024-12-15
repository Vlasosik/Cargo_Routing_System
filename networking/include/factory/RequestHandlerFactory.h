#ifndef REQUESTHANDLERFACTORY_H
#define REQUESTHANDLERFACTORY_H
#include <Poco/Net/HTTPRequestHandlerFactory.h>

class RequestHandlerFactory : public  Poco::Net::HTTPRequestHandlerFactory{
public:
    Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest &request) override;
};
#endif //REQUESTHANDLERFACTORY_H
