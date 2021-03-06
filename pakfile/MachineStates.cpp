// MachineStates.cpp
#include "MachineStates.h"

AbstractState::~AbstractState() {
}

void AbstractState::setState(Machine& machine, AbstractState* state) {
    AbstractState* aux = machine.mState;
    machine.mState = state; 
    delete aux;
}

void AbstractState::updateStock(Machine& machine, unsigned int quantity) {
    machine.mStockQuantity = quantity;
}

Normal::~Normal() {
}

void Normal::sell(Machine& machine, unsigned int quantity) {
    int currStock = machine.getCurrentStock();
    if (currStock < (int)quantity) {
        throw std::runtime_error("Not enough stock");
    }

    updateStock(machine, currStock - quantity);

    if (machine.getCurrentStock() == 0) {
        setState(machine, new SoldOut());
    }
}

void Normal::refill(Machine& machine, unsigned int quantity) {
    int currStock = machine.getCurrentStock();
    updateStock(machine, currStock + quantity);
}

SoldOut::~SoldOut() {
}

void SoldOut::sell(Machine& machine, unsigned int quantity) {
    throw std::runtime_error("Sold out!");
}

void SoldOut::refill(Machine& machine, unsigned int quantity) {
    updateStock(machine, quantity);
    setState(machine, new Normal());
}