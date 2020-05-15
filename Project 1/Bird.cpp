#include "Bird.hpp"
#include <iostream>
using namespace std;

Bird:: Bird() {
    
}
void Bird::setAquatic(bool aquatic) {
    aquatic_ = aquatic;
}
//implementing all functions within the Bird class
void Bird::setAirborne(bool airborne) {
    airborne_ = airborne;
}

bool Bird::isAirborne() {
    return airborne_;
}

bool Bird::isAquatic() {
    return aquatic_;
}