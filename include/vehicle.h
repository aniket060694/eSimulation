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
                probability_fault_hr(probability_fault_hr), fault_probability(probability_fault_hr),
                cur_battery_level(battery_capacity), cur_vehicle_state(state) { }

        int get_vehicle_id(void) { return vehicle_id; }
        double get_battery_capacity(void) { return battery_capacity; }
        double get_cur_battery_level(void) { return cur_battery_level; }
        double get_total_time_to_charge(void) { return time_to_charge; }
        int get_total_charging_sessions(void) { return total_charging_sessions; }
        VehicleState get_vehicle_cur_state(void) { return cur_vehicle_state; }
        bool is_vehicle_cur_flying(void) { return (cur_vehicle_state == VehicleState::FLYING); }
        bool is_vehicle_cur_charging(void) { return (cur_vehicle_state == VehicleState::CHARGING); }
        bool is_vehicle_cur_waiting_for_charging(void) {
            return (cur_vehicle_state == VehicleState::WAITING_FOR_CHARGE); }
        double get_cruise_speed_energy_usage(void) { return energy_use_at_cruise; }
        double get_cur_cruise_speed(void) { return cruise_speed; }
        std::string get_company_name(void) { return company_name; }
        double get_total_flight_time(void) { return total_flight_time; }
        double get_total_distance(void) { return total_distance; }
        double get_total_charging_time(void) { return total_charging_time; }
        int get_total_passenger_count(void) { return total_passenger_count; }
        double get_fault_probability(void) { return fault_probability; }

        void set_vehicle_id(int id) { vehicle_id = id; }
        void set_cur_battery_level(double battery_level) { cur_battery_level = battery_level; }
        void set_vehicle_cur_state(VehicleState state) { cur_vehicle_state = state; }

        void total_charging_time_increase(double time_interval) { total_charging_time += time_interval; }
        void total_charging_sessions_increase(void) { total_charging_sessions++; }
        void total_flight_time_increase(double time_interval) { total_flight_time += time_interval; }
        void total_distance_increase(double distance) { total_distance += distance; }

    private:
        // vehicle configuration
        int vehicle_id{};
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
