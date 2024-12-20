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
                T updatedAt;
                T &operator()() { return updatedAt; }
                const T &operator()() const { return updatedAt; }
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

struct Routes {
private:
    int64_t id{};
    int64_t driverId;
    int64_t vehicleId;
    int64_t cargoesId;
    std::string startPoint;
    std::string endPoint;
    std::string status;
    sqlpp::chrono::microsecond_point createdAt;
    sqlpp::chrono::microsecond_point updatedAt;

public:
    Routes()
        : driverId(0), vehicleId(0), cargoesId(0), createdAt(std::chrono::system_clock::now()),
          updatedAt(std::chrono::system_clock::now()) {
    }

    Routes(int64_t id, int64_t driverId, int64_t vehicleId, int64_t cargoesId,
           std::string startPoint, std::string endPoint, std::string status,
           const sqlpp::chrono::microsecond_point &createdAt, const sqlpp::chrono::microsecond_point &updatedAt)
        : id(id), driverId(driverId), vehicleId(vehicleId), cargoesId(cargoesId),
          startPoint(std::move(startPoint)), endPoint(std::move(endPoint)),
          status(std::move(status)), createdAt(createdAt),
          updatedAt(updatedAt) {
    }

    Routes(int64_t id, int64_t driverId, int64_t vehicleId, int64_t cargoesId,
           std::string startPoint, std::string endPoint, std::string status)
        : id(id), driverId(driverId), vehicleId(vehicleId), cargoesId(cargoesId),
          startPoint(std::move(startPoint)), endPoint(std::move(endPoint)),
          status(std::move(status)), createdAt(std::chrono::system_clock::now()),
          updatedAt(std::chrono::system_clock::now()) {
    }

    Routes(int64_t driverId, int64_t vehicleId, int64_t cargoesId,
           std::string startPoint, std::string endPoint, std::string status)
        : driverId(driverId), vehicleId(vehicleId), cargoesId(cargoesId),
          startPoint(std::move(startPoint)), endPoint(std::move(endPoint)),
          status(std::move(status)), createdAt(std::chrono::system_clock::now()),
          updatedAt(std::chrono::system_clock::now()) {
    }

    [[nodiscard]] int64_t getId() const { return id; }
    [[nodiscard]] int64_t getDriverId() const { return driverId; }
    [[nodiscard]] int64_t getVehicleId() const { return vehicleId; }
    [[nodiscard]] int64_t getCargoesId() const { return cargoesId; }
    [[nodiscard]] std::string getStartPoint() const { return startPoint; }
    [[nodiscard]] std::string getEndPoint() const { return endPoint; }
    [[nodiscard]] std::string getStatus() const { return status; }
    [[nodiscard]] sqlpp::chrono::microsecond_point getCreatedAt() const { return createdAt; }
    [[nodiscard]] sqlpp::chrono::microsecond_point getUpdatedAt() const { return updatedAt; }

    void setId(const int64_t id) { this->id = id; }
    void setDriverId(const int64_t driverId) { this->driverId = driverId; }
    void setVehicleId(const int64_t vehicleId) { this->vehicleId = vehicleId; }
    void setCargoesId(const int64_t cargoesId) { this->cargoesId = cargoesId; }
    void setStartPoint(std::string startPoint) { this->startPoint = std::move(startPoint); }
    void setEndPoint(std::string endPoint) { this->endPoint = std::move(endPoint); }
    void setStatus(std::string status) { this->status = std::move(status); }
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
#endif //ROUTES_H
