#include "factory/RequestHandlerFactory.h"

#include <Poco/Net/HTTPServerRequest.h>

#include "factory/RequestHandlerCargoes.h"

Poco::Net::HTTPRequestHandler *RequestHandlerFactory::
createRequestHandler(const Poco::Net::HTTPServerRequest &request) {
    return new RequestHandlerCargoes();
}
