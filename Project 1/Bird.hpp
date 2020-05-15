#ifndef BIRD_HPP
#define BIRD_HPP
#include "Animal.hpp"
#include <iostream>
using namespace std;

//declaring Bird as a derived class. Animal is the base class
class Bird: public Animal {
    public:
    //Bird's constructor is deriving from the Animal constructor
    //It is passing it's own arguments into the base constructor so that it could construct Bird
        Bird();
        Bird(string name, bool domestic = false, bool predator = false)
        :Animal(name, domestic, predator) {};
    //Public functions to access private members below
        bool isAirborne();
        bool isAquatic();
        void setAirborne(bool airborne = false);
        void setAquatic(bool aquatic = false);
    private:
    //These private variables can only be accessed through public functions above
        bool airborne_;
        bool aquatic_;

};

#endif