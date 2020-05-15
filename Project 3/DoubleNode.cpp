/*
    Student: Richard Aguilar
    Course: CSCI 235 - Software Analysis & Design II
    Term: Spring 2020
    Instructor: Professor Wole Oyekoya
*/

#include "DoubleNode.hpp"
//#include <cstddef>

template<class ItemType>
DoubleNode<ItemType>::DoubleNode() : next(nullptr), previous(nullptr)
{
} // end default constructor

template<class ItemType>
DoubleNode<ItemType>::DoubleNode(const ItemType& anItem) : item(anItem), next(nullptr), previous(nullptr)
{
} // end constructor

template<class ItemType>
DoubleNode<ItemType>::DoubleNode(const ItemType& anItem, DoubleNode<ItemType>* nextNodePtr, DoubleNode<ItemType>* previousNodePtr) :
                item(anItem), next(nextNodePtr), previous(previousNodePtr)
{
} // end constructor

template<class ItemType>
void DoubleNode<ItemType>::setItem(const ItemType& anItem)
{
   item = anItem;
} // end setItem

template<class ItemType>
void DoubleNode<ItemType>::setNext(DoubleNode<ItemType>* nextNodePtr)
{
   next = nextNodePtr;
} // end setNext

template<class ItemType>
void DoubleNode<ItemType>::setPrevious(DoubleNode<ItemType>* previousNodePtr)
{
    previous = previousNodePtr;
}

template<class ItemType>
ItemType DoubleNode<ItemType>::getItem() const
{
   return item;
} // end getItem

template<class ItemType>
DoubleNode<ItemType>* DoubleNode<ItemType>::getNext() const
{
   return next;
} // end getNext

template<class ItemType>
DoubleNode<ItemType>* DoubleNode<ItemType>::getPrevious() const
{
    return previous;
}