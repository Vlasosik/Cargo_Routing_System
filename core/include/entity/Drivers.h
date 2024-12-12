#ifndef DRIVERS_H
#define DRIVERS_H
#include <string>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/type_traits.h>
#include <boost/uuid/uuid.hpp>
#include <sqlpp11/data_types/time_point.h>
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
                T updated_at;
                T &operator()() { return updated_at; }
                const T &operator()() const { return updated_at; }
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

struct TabDrivers {
    int64_t id = 0;
    std::string firstName;
    std::string lastName;
    std::string phone;
    sqlpp::chrono::microsecond_point createdAt;
    sqlpp::chrono::microsecond_point updatedAt;

    TabDrivers() = default;

    explicit TabDrivers(int64_t id, std::string firstName, std::string lastName, std::string phone,
                        sqlpp::chrono::microsecond_point createdAt,
                        sqlpp::chrono::microsecond_point updatedAt)
        : id(id), firstName(std::move(firstName)), lastName(std::move(lastName)), phone(std::move(phone)),
          createdAt(createdAt), updatedAt(updatedAt) {
    }
};
#endif //DRIVERS_H
