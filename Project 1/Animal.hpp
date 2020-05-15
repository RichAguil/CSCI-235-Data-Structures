#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <iostream>
using namespace std;

//declaring the Animal class
class Animal {
    //declaring public functions and variables
    public:
    //declaring constructor for the Animal class
        Animal();
        Animal(string name, bool domestic = false, bool predator = false);
        string getName() const;
        bool isDomestic() const;
        bool isPredator() const;
        void setName(string name);
        void setDomestic(bool domestic = true);
        void setPredator(bool predator = true);
    private:
    //These private variables can only be accessed through public functions above
        string name_;
        bool domestic_;
        bool predator_;
};

#endif