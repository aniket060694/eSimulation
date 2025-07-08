#include "test_module.h"

static void run_basic_test_cases(void);

template <typename arg1>
void test_equal_val(std::string test_name, arg1 first_val, arg1 second_val)
{
    std::cout << "[******* test execute *******] "<< std::endl;
    if (first_val == second_val) {
        std::cout << "[   TEST PASSED  ] "<< test_name << std::endl;
    } else {
        std::cout << "[   TEST FAILED  ] "<< test_name << std::endl;
    }
    std::cout << "[******* test done *******] "<< std::endl;
}

template <typename arg1>
void test_greater_equal_val(std::string test_name, arg1 first_val, arg1 second_val)
{
    std::cout << "[******* test execute *******] "<< std::endl;
    if (first_val >= second_val) {
        std::cout << "[   TEST PASSED  ] "<< test_name << std::endl;
    } else {
        std::cout << "[   TEST FAILED  ] "<< test_name << std::endl;
    }
    std::cout << "[******* test done *******] "<< std::endl;
}

void run_all_test_cases(void)
{
    // Perform basic test cases
    run_basic_test_cases();

    //@TODO Need to add advance test cases
}

void run_basic_test_cases(void)
{
    Simulator obj;

    obj.simulation_start();

    test_equal_val("Total vehicle Test", obj.get_total_vehicles(), MAX_VEHICLES_USED);
    test_equal_val("Total charging station Test", obj.get_total_charging_station(), MAX_NUM_CHARGERS);
    test_greater_equal_val("Total simulation duration Test", obj.get_cur_simulation_time(), MAX_SIMULATION_DURATION_HRS);
}
