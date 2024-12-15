#include <dao/CargoesDAO.h>
#include <sqlpp11/insert.h>
#include <sqlpp11/remove.h>
#include <sqlpp11/select.h>
#include <sqlpp11/update.h>
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

void CargoesDAO::createCargoes(const Cargoes &cargoes) {
    auto cargo = mydb::Cargoes::TabCargoes{};
    auto statement = insert_into(cargo).set(
        cargo.name = cargoes.getName(),
        cargo.weight = cargoes.getWeight(),
        cargo.sender = cargoes.getSender(),
        cargo.receipt = cargoes.getReceipt()
    );
    try {
        db(statement);
        std::cout << "Cargo successfully created!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

Cargoes CargoesDAO::getCargoesById(const int64_t id) {
    if (!isCargoExist(id)) {
        throw std::invalid_argument("Cargo doesn`t exist!");
    }
    auto cargo = mydb::Cargoes::TabCargoes{};
    auto statement = select(cargo.id, cargo.name, cargo.weight, cargo.sender, cargo.receipt, cargo.createdAt,
                            cargo.updated_at).from(cargo).where(cargo.id == id);
    auto result = db(statement);
    const auto& row = result.front();
    Cargoes cargoes;
    cargoes.setId(row.id);
    cargoes.setName(row.name);
    cargoes.setWeight(row.weight);
    cargoes.setSender(row.sender);
    cargoes.setReceipt(row.receipt);
    cargoes.setCreatedAt(row.createdAt);
    cargoes.setUpdatedAt(row.updated_at);
    return cargoes;
}

std::vector<Cargoes> CargoesDAO::getAllCargoes() {
    auto cargo = mydb::Cargoes::TabCargoes{};
    auto statement = select(
                cargo.id, cargo.name, cargo.weight, cargo.sender, cargo.receipt, cargo.createdAt, cargo.updated_at
            ).from(cargo)
            .where(cargo.id == 1);

    auto result = db(statement);
    if (result.empty()) {
        throw std::invalid_argument("Cargoes don`t exist!");
    }
    std::vector<Cargoes> listCargoes;
    for (const auto &row: result) {
        auto createdAt = static_cast<std::chrono::system_clock::time_point>(row.createdAt);
        auto updatedAt = static_cast<std::chrono::system_clock::time_point>(row.updated_at);
        listCargoes.emplace_back(
            row.id, row.name, row.weight, row.sender, row.receipt, createdAt, updatedAt
        );
    }
    return listCargoes;
}

void CargoesDAO::updateCargoes(const Cargoes &cargoes) {
    if (!isCargoExist(cargoes.getId())) {
        throw std::invalid_argument("Cargo doesn`t exist!");
    }
    auto cargo = mydb::Cargoes::TabCargoes{};
    auto statement = update(cargo).set(
        cargo.name = cargoes.getName(),
        cargo.weight = cargoes.getWeight(),
        cargo.sender = cargoes.getSender(),
        cargo.receipt = cargoes.getReceipt(),
        cargo.createdAt = cargoes.getCreatedAt(),
        cargo.updated_at = cargoes.getUpdatedAt()
    ).where(cargo.id == cargoes.getId());
    try {
        db(statement);
        std::cout << "Cargo successfully updated!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

void CargoesDAO::deleteCargoes(const int64_t id) {
    if (!isCargoExist(id)) {
        throw std::invalid_argument("Cargo doesn`t exist!");
    }
    auto cargo = mydb::Cargoes::TabCargoes{};
    auto statement = remove_from(cargo).where(cargo.id == id);
    try {
        db(statement);
        std::cout << "Cargo successfully deleted!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when executing a request: " << e.what() << std::endl;
    }
}

bool CargoesDAO::isCargoExist(const int64_t id) {
    auto cargo = mydb::Cargoes::TabCargoes{};
    auto statement = select(cargo.id).from(cargo).where(cargo.id == id);
    auto result = db(statement);
    return !result.empty();
}
