#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "vehicle.h"
#include "factory_vehicle.h"
#include <memory>
#include <vector>
#include <queue>
#include <ctime>
#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <fstream>

#define MAX_VEHICLES_USED           20
#define MAX_NUM_CHARGERS            3
#define MAX_SIMULATION_DURATION_HRS 3.0

/*
 * Defines the increment of simulated time per simulation interval (in seconds).
 * Calculation: 1 second converted to hours (1 / 3600 hours).
 * (1.0 / 3600.0) = 0.0002777 hours, equivalent to 1 simulated second
 * This means each simulation step effectively advances the simulated scenario by 1 second.
 */
#define SIMULATION_EXECUTE_INTERVAL 0.0002777

#define TELEMETRY_FILE_NAME "result/vehicle_telemetry.csv"

//@TODO A dedeicated logger can be implemented.
#ifdef ENABLE_DEBUG_LOG
#define DEBUG_LOG(message) std::cout << "[DEBUG] " << message << std::endl;
#else
#define DEBUG_LOG(message)
#endif

class Simulator {
    public:
        // constructor
        Simulator(int total_num_vehicles = MAX_VEHICLES_USED,
               int total_num_chargers = MAX_NUM_CHARGERS,
               double simulation_duration_hrs = MAX_SIMULATION_DURATION_HRS);

        void simulation_start(void);
        int get_total_vehicles(void) { return total_vehicles; };
        int get_total_charging_station(void) { return num_chargers; };
        double get_cur_simulation_time(void) { return current_time; };

    private:
        void init_vehicles(int total_num_vehicles);
        void init_charging_station(int total_num_chargers);
        void execute_vehicle_simulation(double time);
        void show_company_performance(void);
        void execute_vehicle_flight(std::unique_ptr<Vehicle> &vehicle, double time_interval);
        void update_vehicle_charging(std::unique_ptr<Vehicle> &vehicle, double time_interval);
#ifdef ENABLE_TELEMETRY_LOG
        // Telemetry methods
        bool is_file_open(void) const;
    
        // If you need to open/reopen the file later (less common for logging managers)
        void open_file(const std::string& filename, bool append = true);
        void close_file(void);
        void init_vehicle_telemetry(void);
        void log_vehicle_telemetry(void);
        void deinit_vehicle_telemetry(void);
#endif //ENABLE_TELEMETRY_LOG

        int total_vehicles{};
        int num_chargers{};
        double simulation_duration_hrs{};
        double time_interval{};
        double current_time{};
        int total_free_charger{};

        std::vector<std::unique_ptr<Vehicle>> vehicles{};
        std::queue<int> vehicle_charger_queue{};
#ifdef ENABLE_TELEMETRY_LOG
        std::ofstream telemetry_output_file{};
#endif //ENABLE_TELEMETRY_LOG
};

#endif // SIMULATOR_H
