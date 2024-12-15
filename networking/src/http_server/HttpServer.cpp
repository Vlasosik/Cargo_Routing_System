#include "http_server/HttpServer.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Stringifier.h>

#include "factory/RequestHandlerFactory.h"

HttpServer::HttpServer(const int port) {
    auto *params = new Poco::Net::HTTPServerParams();
    params->setMaxQueued(100);
    params->setMaxThreads(16);
    Poco::Net::ServerSocket socket(port);
    server = new Poco::Net::HTTPServer(new RequestHandlerFactory, 8080);
}

void HttpServer::start() const {
    std::cout << "Starting server..." << std::endl;
    server->start();
}

void HttpServer::stop() const {
    std::cout << "Stopping server..." << std::endl;
    server->stop();
}
