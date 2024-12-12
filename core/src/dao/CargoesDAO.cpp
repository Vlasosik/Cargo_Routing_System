#include <dao/CargoesDAO.h>
#include <sqlpp11/insert.h>
#include <sqlpp11/select.h>
#include <sqlpp11/postgresql/insert.h>

CargoesDAO::CargoesDAO() {
    sqlpp::postgresql::connection_config config;

    const char *db_user = std::getenv("DB_USER");
    const char *db_password = std::getenv("DB_PASSWORD");
    const char *db_name = std::getenv("DB_NAME");
    const char *db_port = std::getenv("DB_PORT");
    const char *db_host = std::getenv("DB_HOST");

    if (db_user) config.user = db_user;
    if (db_password) config.password = db_password;
    if (db_name) config.dbname = db_name;
    if (db_port) config.port = std::stoi(db_port);
    if (db_host) config.host = db_host;

    db = sqlpp::postgresql::connection(config);
}

void CargoesDAO::createCargoes(const TabCargoes &cargoes) {
    auto cargo = mydb::Cargoes::TabCargoes{};
    auto statement = insert_into(cargo).set(
        cargo.name = cargoes.name,
        cargo.weight = cargoes.weight,
        cargo.sender = cargoes.sender,
        cargo.receipt = cargoes.receipt
    );
    try {
        db(statement);
        std::cout << "Cargo successfully created!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

int64_t CargoesDAO::getCargoesId(int64_t id) {
    if (!isCargoExist(id)) {
        std::cout << "Cargo doesn`t exist!" << std::endl;
    }
    auto cargo = mydb::Cargoes::TabCargoes{};
    auto statement = select(cargo.id).from(cargo).where(cargo.id == id);
    auto result = db(statement);
    return result.front().id;
}

bool CargoesDAO::isCargoExist(int64_t id) {
    auto cargo = mydb::Cargoes::TabCargoes{};
    auto statement = select(cargo.id).from(cargo).where(cargo.id == id);
    auto result = db(statement);
    return !result.empty();
}
