#include "factory/RequestHandlerFactory.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/URI.h>

#include "factory/RequestHandlerCargoes.h"

Poco::Net::HTTPRequestHandler *RequestHandlerFactory::
createRequestHandler(const Poco::Net::HTTPServerRequest &request) {
    Poco::URI uri(request.getURI());
    if (uri.getPath() == "/cargoes") {
        return new RequestHandlerCargoes();
    }
    return nullptr;
}
