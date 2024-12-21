#include "factory/RequestHandlerFactory.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/URI.h>

#include "factory/RequestHandlerCargoes.h"
#include "factory/RequestHandlerDrivers.h"
#include "factory/RequestHandlerVehicles.h"

RequestHandlerFactory::RequestHandlerFactory() {
    // Create cargo request handler
    registerHandler("/cargo", []() { return new RequestHandlerCargoes; });
    registerHandler("/cargo/create", []() { return new RequestHandlerCargoes; });
    registerHandler("/cargo/update", []() { return new RequestHandlerCargoes; });
    registerHandler("/cargo/delete", []() { return new RequestHandlerCargoes; });

    // Create route request handler
    registerHandler("/route", []() { return new RequestHandlerRoutes; });
    registerHandler("/route/create", []() { return new RequestHandlerRoutes; });
    registerHandler("/route/update", []() { return new RequestHandlerRoutes; });
    registerHandler("/route/delete", []() { return new RequestHandlerRoutes; });

    // Create driver request handler
    registerHandler("/driver", []() { return new RequestHandlerDrivers; });
    registerHandler("/driver/create", []() { return new RequestHandlerDrivers; });
    registerHandler("/driver/update", []() { return new RequestHandlerDrivers; });
    registerHandler("/driver/delete", []() { return new RequestHandlerDrivers; });

    // Create vehicle request handler
    registerHandler("/vehicle", []() { return new RequestHandlerVehicles; });
    registerHandler("/vehicle/create", []() { return new RequestHandlerVehicles; });
    registerHandler("/vehicle/update", []() { return new RequestHandlerVehicles; });
    registerHandler("/vehicle/delete", []() { return new RequestHandlerVehicles; });
}

Poco::Net::HTTPRequestHandler *RequestHandlerFactory::
createRequestHandler(const Poco::Net::HTTPServerRequest &request) {
    const Poco::URI uri(request.getURI());
    const std::string &path = uri.getPath();

    if (const auto it = handler.find(path); it != handler.end()) {
        return it->second();
    }
    return nullptr;
}
