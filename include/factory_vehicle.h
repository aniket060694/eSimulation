#ifndef FACTORY_VEHICLE_H
#define FACTORY_VEHICLE_H

#include "vehicle.h"
#include <memory>
#include <string>

class FactoryVehicle {
public:
    enum class VehicleType {
        ALPHA,
        BRAVO,
        CHARLIE,
        DELTA,
        ECHO,
        MAX_VEHICLE
    };

    static std::unique_ptr<Vehicle> create_vehicle(VehicleType type) {
        switch (type) {
            case VehicleType::ALPHA:
                return std::make_unique<Vehicle>(
                    "Alpha Company", //vehicle name
                    120,   //cruise_speed
                    320,   //battery_capacity
                    0.6,   //time_to_charge
                    1.6,   //energy_use_at_cruise
                    4,     //total_passenger_count
                    0.25,  //probability_fault_hr
                    VehicleState::FLYING // vehicle state
                );
            case VehicleType::BRAVO:
                return std::make_unique<Vehicle>(
                    "Bravo Company", //vehicle name
                    100,   //cruise_speed
                    100,   //battery_capacity
                    0.2,   //time_to_charge
                    1.5,   //energy_use_at_cruise
                    5,     //total_passenger_count
                    0.10,  //probability_fault_hr
                    VehicleState::FLYING // vehicle state
                );
            case VehicleType::CHARLIE:
                return std::make_unique<Vehicle>(
                    "Charlie Company", //vehicle name
                    160,   //cruise_speed
                    220,   //battery_capacity
                    0.8,   //time_to_charge
                    2.2,   //energy_use_at_cruise
                    3,     //total_passenger_count
                    0.05,  //probability_fault_hr
                    VehicleState::FLYING // vehicle state
                );
            case VehicleType::DELTA:
                return std::make_unique<Vehicle>(
                    "Delta Company", //vehicle name
                    90,    //cruise_speed
                    120,   //battery_capacity
                    0.62,  //time_to_ciharge
                    0.8,   //energy_use_at_cruise
                    2,     //total_passenger_count
                    0.22,  //probability_fault_hr
                    VehicleState::FLYING // vehicle state
                );
            case VehicleType::ECHO:
                return std::make_unique<Vehicle>(
                    "Echo Company", //vehicle name
                    30,    //cruise_speed
                    150,   //battery_capacity
                    0.3,   //time_to_charge
                    5.8,   //energy_use_at_cruise
                    2,     //total_passenger_count
                    0.61,  //probability_fault_hr
                    VehicleState::FLYING // vehicle state
                );
            default:
                return nullptr;
        }
    }
};

#endif // FACTORY_VEHICLE_H
