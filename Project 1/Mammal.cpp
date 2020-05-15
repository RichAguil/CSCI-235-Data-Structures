#include "Mammal.hpp"
#include <iostream>
using namespace std;

//implementing all functions within the Mammal class
Mammal:: Mammal() {

}

bool Mammal::hasHair() const{
    return hair_;
}

bool Mammal::isAirborne() const{
    return airborne_;
}

bool Mammal::isAquatic() const{
    return aquatic_;
}

bool Mammal::isToothed() const{
    return toothed_;
}

bool Mammal::hasFins() const{
    return fins_;
}

bool Mammal::hasTail() const{
    return tail_;
}

int Mammal::legs() {
    return legs_;
}

void Mammal::setHair(bool hair) {
    hair_ = hair;
}

void Mammal::setAirborne(bool airborne) {
    airborne_ = airborne;
}

void Mammal::setAquatic(bool aquatic) {
    aquatic_ = aquatic;
}

void Mammal::setToothed(bool toothed) {
    toothed_ = toothed;
}

void Mammal::setFins(bool fins) {
    fins_ = fins;
}

void Mammal::setTail(bool tail) {
    tail_ = tail;
}

void Mammal::setLegs(int legs) {
    legs_ = legs;
}