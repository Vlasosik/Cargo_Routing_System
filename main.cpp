#include <iostream>
#include <migration/MigrationSQL.h>
#include "http_server/HttpServer.h"
/*
 *   migration example code
 *   MigrationSQL migration_sql;
 *   migration_sql.executeMigrations("/Users/vlasik/Навчання/С++/code/intelligent_cargo_routing_system/migration_files");
 */
bool keepRunning = true;

void signalHandler(int signal);

int main() {
    signal(SIGINT, signalHandler);
    const HttpServer server(8080);
    server.start();
    while (keepRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        keepRunning = true;
    }
    std::cout << "Server has stopped." << std::endl;
    return 0;
}

void signalHandler(const int signal) {
    if (signal == SIGINT) {
        keepRunning = false;
    }
}
