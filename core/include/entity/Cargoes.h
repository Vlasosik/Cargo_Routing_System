#ifndef CARGOES_H
#define CARGOES_H
#include <string>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/type_traits.h>
#include <sqlpp11/chrono.h>
#include <sqlpp11/table.h>
#include <sqlpp11/data_types/time_point.h>
#include <sqlpp11/data_types/integral/data_type.h>
#include <sqlpp11/data_types/text/data_type.h>


namespace mydb::Cargoes {
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

    struct Name {
        struct _alias_t {
            static constexpr char _literal[] = "name";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T name;
                T &operator()() { return name; }
                const T &operator()() const { return name; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct Weight {
        struct _alias_t {
            static constexpr char _literal[] = "weight";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T weight;
                T &operator()() { return weight; }
                const T &operator()() const { return weight; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::floating_point>;
    };

    struct Sender {
        struct _alias_t {
            static constexpr char _literal[] = "sender";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T sender;
                T &operator()() { return sender; }
                const T &operator()() const { return sender; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct Receipt {
        struct _alias_t {
            static constexpr char _literal[] = "receipt";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T receipt;
                T &operator()() { return receipt; }
                const T &operator()() const { return receipt; }
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
                const sqlpp::time_point &operator()() const { return createdAt; }
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

    struct TabCargoes : sqlpp::table_t<TabCargoes, Id, Name, Weight, Sender, Receipt, CreatedAt, UpdatedAt> {
        struct _alias_t {
            static constexpr char _literal[] = "cargoes";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T tabCargoes;
                T &operator()() { return tabCargoes; }
                const T &operator()() const { return tabCargoes; }
            };
        };
    };
}

struct TabCargoes {
    int64_t id = 0;
    std::string name;
    double weight = 0.0;
    std::string sender;
    std::string receipt;
    sqlpp::time_point createdAt;
    sqlpp::time_point updatedAt;

    TabCargoes() = default;

    explicit TabCargoes(int64_t id, std::string name, double weight, std::string sender, std::string receipt,
                        sqlpp::time_point createdAt,
                        sqlpp::time_point updatedAt)
        : id(id), name(std::move(name)), weight(weight), sender(std::move(sender)), receipt(std::move(receipt)),
          createdAt(createdAt), updatedAt(updatedAt) {
    }
};
#endif //CARGOES_H
