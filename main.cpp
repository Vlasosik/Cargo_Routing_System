#include <iostream>
#include <migration/MigrationSQL.h>

int main() {
    MigrationSQL migration_sql;
    migration_sql.executeMigrations("/Users/vlasik/Навчання/С++/code/intelligent_cargo_routing_system/migration_files");
    return 0;
}
