#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

enum class VehicleState {
    FLYING,
    CHARGING,
    WAITING_FOR_CHARGE,
    MAX_STATE
};

class Vehicle {
    public:
        // Constructor
        Vehicle(std::string company_name, double cruise_speed, double battery_capacity,
            double time_to_charge, double energy_use_at_cruise, int total_passenger_count,
            double probability_fault_hr, VehicleState state) : company_name(company_name),
                cruise_speed(cruise_speed), battery_capacity(battery_capacity),
                time_to_charge(time_to_charge), energy_use_at_cruise(energy_use_at_cruise),
                total_passenger_count(total_passenger_count),
                probability_fault_hr(probability_fault_hr), total_flight_time(0),
                total_distance(0), total_charging_time(0), total_charging_sessions(0),
                total_faults(0), fault_probability(probability_fault_hr),
                cur_battery_level(battery_capacity), cur_vehicle_state(state) { }

    private:
        // vehicle configuration
        std::string company_name{};
        double cruise_speed{};          // mph
        double battery_capacity{};      // kWh
        double time_to_charge{};        // hours
        double energy_use_at_cruise{};  // kWh/mile
        int total_passenger_count{};
        double probability_fault_hr{};

        //Aditional params
        double total_flight_time{};     // hours
        double total_distance{};        // miles
        double total_charging_time{};   // hours
        int total_charging_sessions{};
        int total_faults{};
        double fault_probability{};
        double cur_battery_level{};     // kWh

        // vehicle States
        VehicleState cur_vehicle_state{};
};

#endif // VEHICLE_H
