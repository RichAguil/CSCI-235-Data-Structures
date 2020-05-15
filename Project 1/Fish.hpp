#ifndef FISH_HPP
#define FISH_HPP
#include <iostream>
#include "Animal.hpp"
using namespace std;

//declaring Fish as a derived class. Animal is the base class

class Fish: public Animal {
    public:
    //Fish's constructor is deriving from the Animal constructor
    //It is passing it's own arguments into the base constructor so that it could construct Fish
        Fish();
        Fish(string name, bool domestic = 0, bool predator = false)
        :Animal(name, domestic, predator) {
            void setVenomous(bool venomous = false);
        };
    //Public functions to access private members below
        bool isVenomous();
        void setVenomous(bool venomous = false);
    private:
    //These private variables can only be accessed through public functions above
        bool venomous_;
};

#endif
