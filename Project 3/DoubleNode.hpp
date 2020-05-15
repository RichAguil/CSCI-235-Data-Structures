/*
    Student: Richard Aguilar
    Course: CSCI 235 - Software Analysis & Design II
    Term: Spring 2020
    Instructor: Professor Wole Oyekoya
*/
#ifndef DOUBLENODE_
#define DOUBLENODE_

template<class ItemType>
class DoubleNode
{
private:
   ItemType        item; // A data item
   DoubleNode<ItemType>* next; // Pointer to next node
   DoubleNode<ItemType>* previous; //Pointer to previous node
   
public:
   DoubleNode(); //Default constructor
   DoubleNode(const ItemType& anItem); //Parametrized constructor
   DoubleNode(const ItemType& anItem, DoubleNode<ItemType>* nextNodePtr, DoubleNode<ItemType>* previousNodePtr);
   void setItem(const ItemType& anItem);
   void setNext(DoubleNode<ItemType>* nextNodePtr);
   void setPrevious(DoubleNode<ItemType>* previousNodePtr);
   ItemType getItem() const;
   DoubleNode<ItemType>* getNext() const;
   DoubleNode<ItemType>* getPrevious() const;
}; // end DoubleNode

#include "DoubleNode.cpp"
#endif