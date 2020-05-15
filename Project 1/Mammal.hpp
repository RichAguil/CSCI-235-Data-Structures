#ifndef MAMMAL_HPP
#define MAMMAL_HPP
#include "Animal.hpp"
#include <iostream>
using namespace std;

class Mammal: public Animal {
    public:
    //Mammal's constructor is deriving from the Animal constructor
    //It is passing it's own arguments into the base constructor so that it could construct Animal
        Mammal();
        Mammal(string name, bool domestic = false, bool predator = false)
        :Animal(name, domestic, predator){
            setHair(false);
            setAirborne(false);
            setAquatic(false);
            setToothed(false);
            setFins(false);
            setTail(false);
            setLegs(false);
        };
    //Public functions to access private members below
        bool hasHair() const;
        bool isAirborne() const;
        bool isAquatic() const;
        bool isToothed() const;
        bool hasFins() const;
        bool hasTail() const;
        int legs();
        void setHair(bool hair = false);
        void setAirborne(bool airborne = false);
        void setAquatic(bool aquatic = false);
        void setToothed(bool toothed = false);
        void setFins(bool fins = false);
        void setTail(bool tail = false);
        void setLegs(int legs = false);
    private:
    //These private variables can only be accessed through public functions above
        bool hair_;
        bool airborne_;
        bool aquatic_;
        bool toothed_;
        bool fins_;
        bool tail_;
        int legs_;
};

#endif
