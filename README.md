# eSimulation

This project simulates the operations of Electric Vertical Take-Off and Landing (eVTOL) vehicles,
including flight dynamics and charging processes. It provides a foundational framework for analyzing
vehicle performance and resource management within a simulated environment.

## Design Overview
The simulation is structured around the following core classes:

Simulator Class:
    * Manages the initialization of all simulated vehicles.
    * Manages the execution of the simulation's state machine.

Vehicle Class:
    * Maintains all configuration and operational details pertinent to individual eVTOL vehicles
    (e.g., cruise speed, battery capacity, energy consumption, passenger count).
    * Handles vehicle-specific behaviors within the simulation.

## Building Instructions
To compile and build the simulator executable, follow these steps:

### Build Requirements
Ensure you have the necessary development tools installed on your Linux-based system.
(This code has been tested on Ubuntu 20.04.6 with C++17.)

sudo apt-get update
sudo apt-get install g++ make

Build Commands
Navigate to the project's root directory and execute the following make commands:
Clean previous builds:
make clean

Build the simulator executable:
make

Running the Simulation
After a successful build, you can run the simulator:
make run

Using this make command to test basic simulation test cases:
make test_run

By default, telemetry logs and debug logs are disabled. To enable these features,
use the following make commands (note that this will trigger a recompile):

To enable telemetry logs:
make telemetry_enable

To enable debug logs:
make debug_enable

Test Results
Results from single simulation runs are stored in the result_sample/ directory:
simulator_result.txt (Contains test results)
vehicle_telemetry.csv (Detailed telemetry data captured during the run)
vehicle_states_chart.png (A visualization of vehicle states, plotted based on the `vehicle_telemetry.csv` data)

Future Enhancements
    Enhanced Logging:
        Implement robust logging with runtime-configurable log levels.

    Fault Behavior:
        Currently, the simulation tracks vehicle faults, but there is no
        defined process for handling them. Specific actions to be taken upon a fault need to be discussed and implemented.

    Clang Integration:
        Integrate Clang into the Continuous Integration (CI) pipeline for compilation and advanced static code analysis.

    Improved Debugging Support:
        Further enhance debugging capabilities, including improvements to telemetry
        and debug logging beyond current compile-time toggles.
