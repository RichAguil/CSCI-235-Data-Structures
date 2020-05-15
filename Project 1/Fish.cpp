#include "Fish.hpp"
#include <iostream>
using namespace std;

//implementing all functions within the Fish class
Fish:: Fish() {
    
}
bool Fish::isVenomous() {
    return venomous_;
}

void Fish::setVenomous(bool venomous) {
    venomous_ = venomous;
}