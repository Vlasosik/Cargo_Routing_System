#ifndef HTTPSERVER_H
#define HTTPSERVER_H
#include <Poco/Net/HTTPServer.h>

#include "HttpServer.h"

class HttpServer {
    Poco::Net::HTTPServer *server;

public:
    explicit HttpServer(int port);

    void start() const;

    void stop() const;
};
#endif //HTTPSERVER_H
