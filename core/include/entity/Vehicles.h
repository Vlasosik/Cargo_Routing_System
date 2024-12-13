#ifndef VEHICLES_H
#define VEHICLES_H
#include <string>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/type_traits.h>
#include <sqlpp11/chrono.h>
#include <sqlpp11/table.h>
#include <sqlpp11/data_types/time_point.h>
#include <sqlpp11/data_types/integral/data_type.h>
#include <sqlpp11/data_types/text/data_type.h>


namespace mydb::Vehicles {
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

    struct Brand {
        struct _alias_t {
            static constexpr char _literal[] = "brand";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T brand;
                T &operator()() { return brand; }
                const T &operator()() const { return brand; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct Type {
        struct _alias_t {
            static constexpr char _literal[] = "type";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T type;
                T &operator()() { return type; }
                const T &operator()() const { return type; }
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

    struct TabVehicle : sqlpp::table_t<TabVehicle, Id, Brand, Type, CreatedAt, UpdatedAt> {
        struct _alias_t {
            static constexpr char _literal[] = "vehicles";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T tabVehicle;
                T &operator()() { return tabVehicle; }
                const T &operator()() const { return tabVehicle; }
            };
        };
    };
}

struct Vehicles {
    int64_t id = 0;
    std::string brand;
    std::string type;
    sqlpp::chrono::microsecond_point createdAt;
    sqlpp::chrono::microsecond_point updatedAt;

    Vehicles() = default;

    explicit Vehicles(const int64_t id, std::string brand, std::string type,
                      const sqlpp::chrono::microsecond_point createdAt,
                      const sqlpp::chrono::microsecond_point updatedAt)
        : id(id), brand(std::move(brand)), type(std::move(type)), createdAt(createdAt), updatedAt(updatedAt) {
    }

    [[nodiscard]] int64_t getId() const { return id; }
    [[nodiscard]] std::string getBrand() const { return brand; }
    [[nodiscard]] std::string getType() const { return type; }
    [[nodiscard]] sqlpp::chrono::microsecond_point getCreatedAt() const { return createdAt; }
    [[nodiscard]] sqlpp::chrono::microsecond_point getUpdatedAt() const { return updatedAt; }

    void setId(const int64_t id) { this->id = id; }
    void setBrand(std::string brand) { this->brand = std::move(brand); }
    void setType(std::string type) { this->type = std::move(type); }
    void setCreatedAt(const sqlpp::chrono::microsecond_point createdAt) { this->createdAt = createdAt; }
    void setUpdatedAt(const sqlpp::chrono::microsecond_point updatedAt) { this->updatedAt = updatedAt; }
};
#endif //VEHICLES_H
