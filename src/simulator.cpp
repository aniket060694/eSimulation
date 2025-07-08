#include "simulator.h"

int main(void)
{
    Simulator obj;

    obj.simulation_start();
}

// simulation class constructor
Simulator::Simulator(int total_num_vehicles, int total_num_chargers,
    double simulation_duration_hrs) : total_vehicles(total_num_vehicles),
    num_chargers(total_num_chargers), simulation_duration_hrs(simulation_duration_hrs),
    time_interval(SIMULATION_EXECUTE_INTERVAL), current_time(0.0), total_free_charger(total_num_chargers)
{
    init_vehicles(total_num_vehicles);
}

// Initialize all vehicles info
void Simulator::init_vehicles(int total_num_vehicles)
{
    int c_index;

    //srand is used for random number generation
    std::srand(std::time(nullptr));

    for (int index = 0; index < total_num_vehicles; index++) {
        c_index = std::rand() % (int)(FactoryVehicle::VehicleType::MAX_VEHICLE);
        FactoryVehicle::VehicleType chosen_type = (FactoryVehicle::VehicleType)c_index;

        std::unique_ptr<Vehicle> new_vehicle_ptr =
            FactoryVehicle::create_vehicle(chosen_type);

        new_vehicle_ptr->set_vehicle_id(index);

        if (new_vehicle_ptr) {
            vehicles.push_back(std::move(new_vehicle_ptr));
        } else {
            std::cout << "Warning: Failed to create vehicle of type " << c_index << std::endl;
        }
    }
}

// start the simulation process
void Simulator::simulation_start(void)
{
    //execute vehicle simulation every seconds
    while (current_time < simulation_duration_hrs) {
        execute_vehicle_simulation(time_interval);
        current_time += time_interval;
    }

    show_company_performance();
}

void Simulator::execute_vehicle_simulation(double time_interval)
{
    // Update state of all flying vehicle
    for (std::unique_ptr<Vehicle> &vehicle : vehicles) {
        if (vehicle->is_vehicle_cur_flying()) {
            execute_vehicle_flight(vehicle, time_interval);

            // The vehicle battery is fully drained. Add it to the charging queue.
            if (vehicle->get_cur_battery_level() <= 0) {
                vehicle_charger_queue.push(vehicle->get_vehicle_id());
                vehicle->set_vehicle_cur_state(VehicleState::WAITING_FOR_CHARGE);
            }
        } else if (vehicle->is_vehicle_cur_charging()) {
            // update vehicle charging information and state if fully charged
            update_vehicle_charging(vehicle, time_interval);
        }
    }

    // Check If any charger is available
    while (total_free_charger > 0) {
        // Check If any vehicle is waiting for charge
        if (!vehicle_charger_queue.empty()) {
                // Check If any vehicle is waiting for charge
                int vehicle_id = vehicle_charger_queue.front();
                vehicle_charger_queue.pop();
                vehicles[vehicle_id]->set_vehicle_cur_state(VehicleState::CHARGING);
                total_free_charger--;
            } else {
                break;
	    }
        }
}

void Simulator::execute_vehicle_flight(std::unique_ptr<Vehicle> &vehicle, double time_interval)
{   
    DEBUG_LOG("execute vehicle flight function");
    double cur_energy_usage = vehicle->get_cruise_speed_energy_usage() *
        vehicle->get_cur_cruise_speed() * time_interval;
    
    vehicle->total_flight_time_increase(time_interval);
    vehicle->total_distance_increase(vehicle->get_cur_cruise_speed() * time_interval);
    
    DEBUG_LOG("Battery Level before draining: " << vehicle->get_cur_battery_level());
    double new_battery_level = vehicle->get_cur_battery_level() - cur_energy_usage;
    
    if (new_battery_level < 0) {
        new_battery_level = 0;
    }
    
    vehicle->set_cur_battery_level(new_battery_level);
    DEBUG_LOG("Battery Level after draining: " << vehicle->get_cur_battery_level());
    
    if (vehicle->get_cur_battery_level() == 0) {
        DEBUG_LOG("vehicle battery drained. Transitioning to charging.");
        vehicle->set_vehicle_cur_state(VehicleState::WAITING_FOR_CHARGE);
    }
}

void Simulator::update_vehicle_charging(std::unique_ptr<Vehicle> &vehicle, double time_interval)
{
    double total_time_to_charge = vehicle->get_total_time_to_charge();
    double max_charge_time_per_hr = vehicle->get_battery_capacity() / total_time_to_charge;
    double max_cur_charge = time_interval * max_charge_time_per_hr;
    double charging_needed = vehicle->get_battery_capacity() - vehicle->get_cur_battery_level();
    double charge_amount = std::min(max_cur_charge, charging_needed);
    double old_battery_level = vehicle->get_cur_battery_level();
    double new_battery_level = old_battery_level + charge_amount;

    vehicle->set_cur_battery_level(new_battery_level);
    vehicle->total_charging_time_increase(time_interval);

    //Check vehicle battery is fully changed.
    if ((new_battery_level >= vehicle->get_battery_capacity())) {
        // Increment total charging sessions
        vehicle->total_charging_sessions_increase();
        DEBUG_LOG("Total number of charging sessions:" << vehicle->get_total_charging_sessions());
        // Increase free charger
        total_free_charger++;
        vehicle->set_vehicle_cur_state(VehicleState::FLYING);
    }
}

void Simulator::show_company_performance(void)
{
    std::unordered_map<std::string, std::vector<int>> vehicles_map;

    for (std::unique_ptr<Vehicle> &vehicle : vehicles) {
        vehicles_map[vehicle->get_company_name()].push_back(vehicle->get_vehicle_id());
    }

    for (const auto& [company, vehicle_id_list] : vehicles_map) {
        double total_flight_time = 0.0;
        double total_distance = 0.0;
        double total_charging_time = 0.0;
        int num_charging_sessions = 0;
        int total_num_flights = 0;
        double total_num_passenger_miles = 0.0;
        double total_faults = 0.0;

        for (auto vehicle_id : vehicle_id_list) {
            std::unique_ptr<Vehicle> &vehicle = vehicles[vehicle_id];
            total_flight_time += vehicle->get_total_flight_time();
            total_distance += vehicle->get_total_distance();
            total_charging_time += vehicle->get_total_charging_time();
            num_charging_sessions += vehicle->get_total_charging_sessions();
            total_num_flights++;
            total_num_passenger_miles += vehicle->get_total_distance() * vehicle->get_total_passenger_count();

            DEBUG_LOG("Fault Probability: " << vehicle->get_fault_probability());
            double fault_probability_hr = vehicle->get_fault_probability();
            double vehicle_faults = vehicle->get_total_flight_time() * fault_probability_hr;

            total_faults += vehicle_faults;
        }

        if (total_num_flights == 0) {
            std::cout << "Error: No total num of flights." << std::endl;
            continue;
        }

        std::cout << "==================================================" << std::endl;
        std::cout << "Company: " << company << std::endl;
        std::cout << "Number of vehicles:" << vehicle_id_list.size() << std::endl;
        std::cout << "Average flight time: per flight " << total_flight_time / total_num_flights
            << " hr" << std::endl;
        std::cout << "Average distance traveled per Flight: " << total_distance / total_num_flights
            << " miles" << std::endl;

        if (num_charging_sessions == 0) {
            std::cout << "Average time charging per charge session: " << "No charging sessions." << std::endl;
        } else {
            std::cout << "Average time charging per charge session: " <<
                total_charging_time / num_charging_sessions << " hr" << std::endl;
        }

        //Round the faults value
        std::cout << "Number num of faults: " << std::round(total_faults) << std::endl;
        std::cout << "Total num of passenger miles: " << total_num_passenger_miles << std::endl;
        std::cout << "==================================================" << std::endl;
        std::cout << std::endl;
    }
}
