#include <iostream>
#include "Animal.hpp"
using namespace std;

//defining the Animal constructor
Animal:: Animal() {

}
Animal::Animal(string name, bool domestic, bool predator) {
    setName(name);
    setDomestic(domestic);
    setPredator(predator);
}
//implementing all functions within the Animal class
void Animal::setName(string name){
    name_ = name;
} 

void Animal::setDomestic(bool domestic) {
    domestic_ = domestic;
}

void Animal::setPredator(bool predator) {
    predator_ = predator;
}

bool Animal::isDomestic() const{
    return domestic_;
}

bool Animal::isPredator() const{
    return predator_;
}

string Animal::getName() const{
    return name_;
}