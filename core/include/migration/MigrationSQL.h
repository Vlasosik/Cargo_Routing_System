#ifndef MIGRATIONSQL_H
#define MIGRATIONSQL_H
#include <sqlpp11/postgresql/postgresql.h>
#include <fstream>
class MigrationSQL {
    std::string migrationSQL;
    sqlpp::postgresql::connection db;
public:
    MigrationSQL();
    MigrationSQL(const std::string &user, const std::string &password, const std::string &dbname,
                 int port, const std::string &host);

    void executeMigrations(const std::string &migrationFolder);
};
#endif //MIGRATIONSQL_H
