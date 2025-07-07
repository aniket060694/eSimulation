#include "simulation_main.h"

int main(void)
{
    SimulationMain obj;

    obj.simulation_start();
}

// simulation class constructor
SimulationMain::SimulationMain(int total_num_vehicles, int total_num_chargers,
    double simulation_duration_hrs) : total_vehicles(total_num_vehicles),
    num_chargers(total_num_chargers), simulation_duration_hrs(simulation_duration_hrs),
    time_interval(SIMULATION_EXECUTE_INTERVAL), current_time(0.0)
{
    init_vehicles(total_num_vehicles);
    init_charging_station(total_num_chargers);
}

// Initialize all vehicles info
void SimulationMain::init_vehicles(int total_num_vehicles)
{
    int c_index;

    //srand is used for random number generation
    std::srand(std::time(nullptr));

    for (int index = 0; index < total_num_vehicles; index++) {
        c_index = std::rand() % (int)(FactoryVehicle::VehicleType::MAX_VEHICLE);
        FactoryVehicle::VehicleType chosen_type = (FactoryVehicle::VehicleType)c_index;

        std::shared_ptr<Vehicle> new_vehicle_ptr =
            FactoryVehicle::create_vehicle(chosen_type);

        if (new_vehicle_ptr) {
            vehicles.push_back(new_vehicle_ptr);
        } else {
            std::cout << "Warning: Failed to create vehicle of type " << c_index << std::endl;
        }
    }
}

// Initialize chargers objects
void SimulationMain::init_charging_station(int total_num_chargers)
{
    for (int index = 0; index < total_num_chargers; index++) {
        // Create a new charger using the charger_factory
        chargers_info.push_back(std::make_shared<ChargingStation>());
    }
}

// start the simulation process
void SimulationMain::simulation_start(void)
{
    //execute vehicle simulation
}
