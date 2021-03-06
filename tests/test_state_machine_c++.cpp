#include <iostream>
#include <stdexcept>
#include "Machine.h"
#include "MachineStates.h"

int main() {
    Machine m1(10), m2(0);

    m1.sell(10);
    std::cout << "m1: " << "Sold 10 items" << std::endl;

    try {
        m1.sell(1);
    } catch (std::exception& e) {
        std::cerr << "m1: " << e.what() << std::endl;
    }

    m1.refill(20);
    std::cout << "m1: " << "Refilled 20 items" << std::endl;

    m1.sell(10);
    std::cout << "m1: " << "Sold 10 items" << std::endl;
    std::cout << "m1: " << "Remaining " << m1.getCurrentStock() << " items" << std::endl;

    m1.sell(5);
    std::cout << "m1: " << "Sold 5 items" << std::endl;
    std::cout << "m1: " << "Remaining " << m1.getCurrentStock() << " items" << std::endl;

    try {
        m1.sell(10);
    } catch (std::exception& e) {
        std::cerr << "m1: " << e.what() << std::endl;
    }

    try {
        m2.sell(1);
    } catch (std::exception& e) {
        std::cerr << "m2: " << e.what() << std::endl;
    }

    return 0;
}