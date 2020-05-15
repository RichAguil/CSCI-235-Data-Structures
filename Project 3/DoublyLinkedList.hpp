/*
    Student: Richard Aguilar
    Course: CSCI 235 - Software Analysis & Design II
    Term: Spring 2020
    Instructor: Professor Wole Oyekoya
*/

#ifndef DOUBLYLINKEDLIST_
#define DOUBLYLINKEDLIST_

#include <string>
#include <algorithm>
#include "DoubleNode.hpp"

template<class ItemType>
class DoublyLinkedList
{

private:
   DoubleNode<ItemType>* headPtr; // Pointer to first node
   int itemCount;           // Current count of list items
   
public:
   DoublyLinkedList(); //Default constructor
   DoublyLinkedList(ItemType entries[], int entryCount); //Parametrized constructor
   DoublyLinkedList(const DoublyLinkedList<ItemType>& DoubleList); // Copy constructor
   virtual ~DoublyLinkedList();                       // Destructor should be virtual
   bool insert(const ItemType& item, const int& position);
   bool remove(const int& position);
   int getSize() const;
   DoubleNode<ItemType> *getHeadPtr() const;
   DoubleNode<ItemType> *getAtPos(const int& pos) const;
   bool isEmpty() const;
   void clear();
   void display() const;
   void displayBackwards() const;
   DoublyLinkedList<ItemType> interleave(const DoublyLinkedList<ItemType>& a_list);
}; // end LinkedBag

#include "DoublyLinkedList.cpp"
#endif