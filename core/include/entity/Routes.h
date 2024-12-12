#ifndef ROUTES_H
#define ROUTES_H
#include <string>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/type_traits.h>
#include <sqlpp11/chrono.h>
#include <sqlpp11/table.h>
#include <sqlpp11/data_types/time_point.h>
#include <sqlpp11/data_types/integral/data_type.h>
#include <sqlpp11/data_types/text/data_type.h>

namespace mydb::Routes {
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

    struct DriverId {
        struct _alias_t {
            static constexpr char _literal[] = "driver_id";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T driverId;
                T &operator()() { return driverId; }
                const T &operator()() const { return driverId; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::bigint>;
    };

    struct VehiclesId {
        struct _alias_t {
            static constexpr char _literal[] = "vehicles_id";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T vehiclesId;
                T &operator()() { return vehiclesId; }
                const T &operator()() const { return vehiclesId; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::bigint>;
    };

    struct CargoesId {
        struct _alias_t {
            static constexpr char _literal[] = "cargoes_id";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T cargoesId;
                T &operator()() { return cargoesId; }
                const T &operator()() const { return cargoesId; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::bigint>;
    };

    struct StartPoint {
        struct _alias_t {
            static constexpr char _literal[] = "start_point";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T startPoint;
                T &operator()() { return startPoint; }
                const T &operator()() const { return startPoint; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct EndPoint {
        struct _alias_t {
            static constexpr char _literal[] = "end_point";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T endPoint;
                T &operator()() { return endPoint; }
                const T &operator()() const { return endPoint; }
            };
        };

        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };


    struct Status {
        struct _alias_t {
            static constexpr char _literal[] = "status";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T status;
                T &operator()() { return status; }
                const T &operator()() const { return status; }
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

    struct TabRoutes : sqlpp::table_t<TabRoutes, Id, DriverId, VehiclesId, CargoesId, StartPoint, EndPoint, Status,
                CreatedAt, UpdatedAt> {
        struct _alias_t {
            static constexpr char _literal[] = "routes";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;

            template<typename T>
            struct _member_t {
                T tabRoutes;
                T &operator()() { return tabRoutes; }
                const T &operator()() const { return tabRoutes; }
            };
        };
    };
}

struct TabRoutes {
    int64_t id;
    int64_t driverId;
    int64_t vehicleId;
    int64_t cargoesId;
    std::string startPoint;
    std::string endPoint;
    std::string status;
    sqlpp::time_point createdAt;
    sqlpp::time_point updatedAt;

    TabRoutes() = default;

    explicit TabRoutes(const int64_t id, const int64_t driverId, const int64_t vehicleId, const int64_t cargoesId,
                       std::string startPoint,
                       std::string endPoint, std::string status, const sqlpp::time_point createdAt,
                       const sqlpp::time_point updatedAt)
        : id(id), driverId(driverId), vehicleId(vehicleId), cargoesId(cargoesId), startPoint(std::move(startPoint)),
          endPoint(std::move(endPoint)), status(std::move(status)), createdAt(createdAt), updatedAt(updatedAt) {
    }
};
#endif //ROUTES_H
