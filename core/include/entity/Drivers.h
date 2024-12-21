#ifndef DRIVERS_H
#define DRIVERS_H
#include <string>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/type_traits.h>
#include <boost/uuid/uuid.hpp>
#include <sqlpp11/data_types/time_point.h>
#include <sqlpp11/data_types/integral/data_type.h>
#include <sqlpp11/data_types/text/data_type.h>

namespace mydb::Drivers {
    struct Id {
        struct _alias_t {
            static constexpr char _literal[] = "id";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T id;
                T &operator()() { return id; }
                const T &operator()() const { return id; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::bigint>;
    };

    struct FirstName {
        struct _alias_t {
            static constexpr char _literal[] = "first_name";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T firstName;
                T &operator()() { return firstName; }
                const T &operator()() const { return firstName; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct LastName {
        struct _alias_t {
            static constexpr char _literal[] = "last_name";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T lastName;
                T &operator()() { return lastName; }
                const T &operator()() const { return lastName; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct Phone {
        struct _alias_t {
            static constexpr char _literal[] = "phone";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T phone;
                T &operator()() { return phone; }
                const T &operator()() const { return phone; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct CreatedAt {
        struct _alias_t {
            static constexpr char _literal[] = "created_at";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T createdAt;
                T &operator()() { return createdAt; }
                const T &operator()() const { return createdAt; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::time_point>;
    };

    struct UpdatedAt {
        struct _alias_t {
            static constexpr char _literal[] = "updated_at";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T updatedAt;
                T &operator()() { return updatedAt; }
                const T &operator()() const { return updatedAt; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::time_point>;
    };

    struct TabDrivers : sqlpp::table_t<TabDrivers, Id, FirstName, LastName, Phone, CreatedAt, UpdatedAt> {
        struct _alias_t {
            static constexpr char _literal[] = "drivers";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T tabDrivers;
                T &operator()() { return tabDrivers; }
                const T &operator()() const { return tabDrivers; }
            };
        };
    };
}

struct Drivers {
private:
    int64_t id = 0;
    std::string firstName;
    std::string lastName;
    std::string phone;
    sqlpp::chrono::microsecond_point createdAt;
    sqlpp::chrono::microsecond_point updatedAt;
public:
    Drivers() : createdAt(std::chrono::system_clock::now()), updatedAt(std::chrono::system_clock::now()) {
    }

    Drivers(int64_t id, std::string firstName, std::string lastName, std::string phone,
            sqlpp::chrono::microsecond_point createdAt,
            sqlpp::chrono::microsecond_point updatedAt)
        : id(id), firstName(std::move(firstName)), lastName(std::move(lastName)), phone(std::move(phone)),
          createdAt(createdAt), updatedAt(updatedAt) {
    }

    Drivers(int64_t id, std::string firstName, std::string lastName, std::string phone)
        : id(id), firstName(std::move(firstName)), lastName(std::move(lastName)), phone(std::move(phone)),
          createdAt(std::chrono::system_clock::now()), updatedAt(std::chrono::system_clock::now()) {
    }

    Drivers(std::string firstName, std::string lastName, std::string phone)
        : firstName(std::move(firstName)), lastName(std::move(lastName)), phone(std::move(phone)),
          createdAt(std::chrono::system_clock::now()), updatedAt(std::chrono::system_clock::now()) {
    }

    [[nodiscard]] int64_t getId() const { return id; }
    [[nodiscard]] std::string getFirstName() const { return firstName; }
    [[nodiscard]] std::string getLastName() const { return lastName; }
    [[nodiscard]] std::string getPhone() const { return phone; }
    [[nodiscard]] sqlpp::chrono::microsecond_point getCreatedAt() const { return createdAt; }
    [[nodiscard]] sqlpp::chrono::microsecond_point getUpdatedAt() const { return updatedAt; }

    void setId(const int64_t id) { this->id = id; }
    void setFirstName(std::string firstName) { this->firstName = std::move(firstName); }
    void setLastName(std::string lastName) { this->lastName = std::move(lastName); }
    void setPhone(std::string phone) { this->phone = std::move(phone); }
    void setCreatedAt(const sqlpp::chrono::microsecond_point createdAt) { this->createdAt = createdAt; }
    void setUpdatedAt(const sqlpp::chrono::microsecond_point updatedAt) { this->updatedAt = updatedAt; }

    static std::string formatTimeToString(const sqlpp::chrono::microsecond_point &timePoint) {
        using namespace std::chrono;
        auto time = system_clock::to_time_t(timePoint);
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
};
#endif //DRIVERS_H
