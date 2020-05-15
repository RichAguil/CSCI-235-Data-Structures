#include <iostream>
#include <string>
#include <cstddef>
#include <algorithm>
#include "DoubleNode.hpp"
#include "DoublyLinkedList.hpp"
//#include "Linkedlist.cpp"
using namespace std;

int main() {

    string firstArray[4] = {"uno", "dos", "tres", "quatro"};
    DoublyLinkedList<string> firstList(firstArray, 4);
    //firstList.getAtPos(3);
    //firstList.remove(4);
    //firstList.remove(4);
    //firstList.display();
    //firstList.remove(3);
    string secondArray[6] = {"cinco", "seis", "siete", "ocho", "nueve", "diez"};
    DoublyLinkedList<string> secondList(secondArray, 6);
    firstList.interleave(secondList);

    return 0;
}