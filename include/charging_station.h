#ifndef CHARGING_STATION_H
#define CHARGING_STATION_H

#include <iostream>
#include <memory>
#include "vehicle.h"

class ChargingStation {
public:
    // Constructor
    ChargingStation(void);

private:
    bool is_charger_free{};
    double rem_charge_time{};
    // Pointer to the currently charging vehicle
    std::shared_ptr<Vehicle> vehicle_obj{};
};

#endif // CHARGING_STATION_H
