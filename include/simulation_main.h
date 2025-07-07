#ifndef SIMULATION_MAIN_H
#define SIMULATION_MAIN_H

#include "vehicle.h"
#include "charging_station.h"
#include "factory_vehicle.h"
#include <memory>
#include <vector>
#include <queue>
#include <ctime>
#include <iostream>

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

class SimulationMain {
    public:
        // constructor
        SimulationMain(int total_num_vehicles = MAX_VEHICLES_USED,
               int total_num_chargers = MAX_NUM_CHARGERS,
               double simulation_duration_hrs = MAX_SIMULATION_DURATION_HRS);

        void simulation_start(void);

    private:
        void init_vehicles(int total_num_vehicles);
        void init_charging_station(int total_num_chargers);
        void execute_vehicle_simulation(double time);
        void show_company_performance(void);
        void execute_vehicle_flight(std::shared_ptr<Vehicle> vehicle, double time_interval);

        int total_vehicles{};
        int num_chargers{};
        double simulation_duration_hrs{};
        double time_interval{};
        double current_time{};

        std::vector<std::shared_ptr<Vehicle>> vehicles{};
        std::vector<std::shared_ptr<ChargingStation>> chargers_info{};
        std::queue<std::shared_ptr<Vehicle>> vehicle_charger_queue{};
};

#endif // SIMULATION_MAIN_H
