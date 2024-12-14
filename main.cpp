#include <iostream>
#include <migration/MigrationSQL.h>

#include "http_server/HttpServer.h"
/*
 *   migration example code
 *   MigrationSQL migration_sql;
 *   migration_sql.executeMigrations("/Users/vlasik/Навчання/С++/code/intelligent_cargo_routing_system/migration_files");
 */
int main() {
    HttpServer server(8080);
    server.start();
    return 0;
}