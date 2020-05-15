//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT bag: Link-based implementation.
    @file LinkedBag.cpp */
#include <iostream>
#include <string>
#include "LinkedBag.h"
#include "Node.h"
#include <cstddef>
using namespace std;

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

template <class ItemType>
LinkedBag<ItemType>::LinkedBag(ItemType entries[], int entryCount) 
{
   itemCount = entryCount;
   headPtr = new Node<ItemType>(); //Creating head pointer
   headPtr->setItem(entries[0]); //Inserting first index in array into zeroth node
   Node<ItemType>* currentPtr = headPtr;

   for (int i = 1; i < entryCount; i++) { //Looping through array to insert each index into a node and attach it to the linked list
      Node<ItemType>* newItem = new Node<ItemType>();
      newItem->setItem(entries[i]);
      currentPtr->setNext(newItem);
      currentPtr = currentPtr->getNext();
   }
}

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag)
{
	itemCount = aBag.itemCount;
   Node<ItemType>* origChainPtr = aBag.headPtr;  // Points to nodes in original chain
   
   if (origChainPtr == nullptr)
   {
      headPtr = nullptr;  // Original bag is empty
      //Node<ItemType>* recursivePtr = headPtr;
   } else
   {
      // Copy first node
      headPtr = new Node<ItemType>();
      headPtr->setItem(origChainPtr->getItem());
      
      // Copy remaining nodes
      //Node<ItemType>* recursivePtr = headPtr;
      Node<ItemType>* newChainPtr = headPtr;      // Points to last node in new chain
      origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer
      
      while (origChainPtr != nullptr)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();
              
         // Create a new node containing the next item
         Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
         
         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);
         
         // Advance pointer to new last node
         newChainPtr = newChainPtr->getNext();

         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }  // end while
      
      newChainPtr->setNext(nullptr);              // Flag end of chain
   }  // end if
}  // end copy constructor

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag()
{
   clear();
}  // end destructor

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const
{
	Node<ItemType>* currentPtr = headPtr;
   int iteration = 1;

   if (currentPtr == nullptr) {
      iteration--;
      return iteration;
   }

   while (currentPtr->getNext() != nullptr) { //Moving current pointer from one node to the next until it gets to the last node
      iteration++;
      currentPtr = currentPtr->getNext();
   }

   return iteration;
}  // end getCurrentSize

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSizeRecursive() const
{
   static Node<ItemType> *currentPtr = headPtr;
   
   if (currentPtr == nullptr) {//Base case
      return 0; 
   } else { //Else, method will call itself
      currentPtr = currentPtr->getNext();
      return 1 + getCurrentSizeRecursive();
   }

}

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry)
{
   // (headPtr is null if chain is empty)   
   Node<ItemType>* currentPtr = headPtr;  
   Node<ItemType>* nextNodePtr = new Node<ItemType>();
   nextNodePtr->setItem(newEntry);

   if (headPtr == nullptr) {
      headPtr = nextNodePtr;
      itemCount++;
      return true;
   }
   //Node<ItemType>* nextNodePtr = new Node<ItemType>(newEntry, headPtr); // alternate code
   while (currentPtr->getNext() != nullptr) { //This block of code controls the two pointers. It increments both until a node pointing to null is found
      currentPtr = currentPtr -> getNext();
   }

   currentPtr->setNext(nextNodePtr); //Set node pointing to null to instead point to the new entry thereby adding node to end of list
   itemCount++;
   
   return true;
}  // end add

template<class ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const
{
   std::vector<ItemType> bagContents;
   Node<ItemType>* curPtr = headPtr;
   int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
   {
		bagContents.push_back(curPtr->getItem());
      curPtr = curPtr->getNext();
      counter++;
   }  // end while
   
   return bagContents;
}  // end toVector

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry)
{
   Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
   bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
   if (canRemoveItem)
   {
      // Copy data from first node to located node
      entryNodePtr->setItem(headPtr->getItem());
      
      // Delete first node
      Node<ItemType>* nodeToDeletePtr = headPtr;
      headPtr = headPtr->getNext();
      
      // Return node to the system
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr;
      
      itemCount--;
   } // end if
   
	return canRemoveItem;
}  // end remove

template<class ItemType>
void LinkedBag<ItemType>::clear()
{
   Node<ItemType>* nodeToDeletePtr = headPtr;
   while (headPtr != nullptr)
   {
      headPtr = headPtr->getNext();

      // Return node to the system
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;
      
      nodeToDeletePtr = headPtr;
   }  // end while
   // headPtr is nullptr; nodeToDeletePtr is nullptr
   
	itemCount = 0;
}  // end clear

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	int frequency = 0;
   int counter = 0;
   Node<ItemType>* curPtr = headPtr;
   while ((curPtr != nullptr) && (counter < itemCount))
   {
      if (anEntry == curPtr->getItem())
      {
         frequency++;
      } // end if
      
      counter++;
      curPtr = curPtr->getNext();
   } // end while
   
	return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
	return (getPointerTo(anEntry) != nullptr);
}  // end contains

/* ALTERNATE 1
template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
   return getFrequencyOf(anEntry) > 0;
} 
*/
/* ALTERNATE 2 
template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
   bool found = false;
   Node<ItemType>* curPtr = headPtr;
   int i = 0;
   while (!found && (curPtr != nullptr) && (i < itemCount))
   {
      if (anEntry == curPtr-<getItem())
      {
         found = true;
      }
      else
      {
         i++;
         curPtr = curPtr->getNext();
      }  // end if
   }  // end while

   return found;
}  // end contains
*/

// private
// Returns either a pointer to the node containing a given entry 
// or the null pointer if the entry is not in the bag.
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const
{
   bool found = false;
   Node<ItemType>* curPtr = headPtr;
   
   while (!found && (curPtr != nullptr))
   {
      if (anEntry == curPtr->getItem())
         found = true;
      else
         curPtr = curPtr->getNext();
   } // end while
   
   return curPtr;
} // end getPointerTo


template<class ItemType>
void LinkedBag<ItemType>::printList() const //Created this method for myself to show contents of linked list
{
	Node <ItemType>* curPtr = headPtr;
   while (curPtr != nullptr) {
      cout<<curPtr->getItem()<<endl;
      curPtr = curPtr->getNext();
   }
} 

template <class ItemType>
void LinkedBag<ItemType>::deleteSecondNode() const 
{
   Node <ItemType>*curPtr = headPtr;

   if (headPtr != nullptr) {

      curPtr = curPtr->getNext();
      if(curPtr->getNext() != nullptr) { //if linked list has more than two nodes
         headPtr->setNext(curPtr->getNext()); //Set head pointer to point to the third node if a node exists after the second one
         curPtr->setNext(nullptr); //Set pointer to second node equal to null
      } else {
         headPtr->setNext(nullptr); //If only two nodes in the linked list, simply set pointer to second node equal to null
      }
   }

}

template<class ItemType>
void LinkedBag<ItemType>::removeRandom() const
{
   int randEntry = rand()%getCurrentSize(); //Generates a random number based off of current size
   Node <ItemType>*curPtr = headPtr; //Initializes first pointer
   Node <ItemType>*trailPtr = headPtr; //Initializes a second pointer to trail the first

   if (randEntry == 0) {
      headPtr->setNext(headPtr->getNext()); //if the node to be deleted is first node, set head to point to second node
   } else {

      curPtr = curPtr->getNext(); //Moves up first pointer to first index in linked list

      for (int i = 1; i < randEntry; i++) {
         trailPtr = trailPtr->getNext(); //Trailing pointer always points to node behind current pointer
         curPtr = curPtr->getNext();
      }

      if (curPtr->getNext() != nullptr) {
         trailPtr->setNext(curPtr->getNext()); //Once node is found, set trailing pointer to point to node after the one being deleted
         curPtr->setNext(nullptr); //Set pointer of node to be deleted to null
      } else {
         trailPtr->setNext(nullptr); //If there is no nodes after the node selected to be deleted, simply set pointer before it to null
      }

   }
}