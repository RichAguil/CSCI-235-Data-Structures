/*
    Student: Richard Aguilar
    Course: CSCI 235 - Software Analysis & Design II
    Term: Spring 2020
    Instructor: Professor Wole Oyekoya
*/

#include <iostream>
#include <string>
#include "DoublyLinkedList.hpp"
#include <cstddef>
#include <algorithm>
using namespace std;

template<class ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList() : headPtr(nullptr), itemCount(0)
{

}  //End default constructor


/*
The below parametrized constructor merely creates a Doubly Linked List using arrays as one of the arguments. This function was created to make to build
large lists so that they could be tested
*/
template <class ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList(ItemType entries[], int entryCount) 
{
   itemCount = entryCount;
   headPtr = new DoubleNode<ItemType>(); //Creating head pointer
   headPtr->setItem(entries[0]); //Setting the head pointer data value to the zeroth value in the array
   //Created two pointers here to more easily link nodes together both forwards and backwards
   DoubleNode<ItemType>* currentPtr = headPtr;
   DoubleNode<ItemType>* trailingPtr = headPtr;

   for (int i = 1; i < entryCount; i++) { //Looping through array to insert each index into a node and attach it to the linked list
      DoubleNode<ItemType>* newItem = new DoubleNode<ItemType>();
      newItem->setItem(entries[i]);
      currentPtr->setNext(newItem);
      currentPtr = currentPtr->getNext();
      currentPtr->setPrevious(trailingPtr);
      trailingPtr = trailingPtr->getNext();
   }
}

template<class ItemType> //Copy constructor
DoublyLinkedList<ItemType>::DoublyLinkedList(const DoublyLinkedList<ItemType>& DoubleList)
{
   itemCount = DoubleList.itemCount;
   DoubleNode<ItemType>* origChainPtr = DoubleList.headPtr;  // Points to nodes in original chain
   
   if (origChainPtr == nullptr)
   {
      headPtr = nullptr;  //Original bag is empty

   } else {
      //Copy first node
      headPtr = new DoubleNode<ItemType>();
      headPtr->setItem(origChainPtr->getItem());
      
      //Copy remaining nodes
 
      DoubleNode<ItemType>* newChainPtr = headPtr;      //Created two pointers here for the same purpose as the ones in the previous constructor
      DoubleNode<ItemType>* trailingPtr = headPtr;
      origChainPtr = origChainPtr->getNext();     //Advance original-chain pointer
      
      while (origChainPtr != nullptr)
      {
         //Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();
              
         //Create a new node containing the next item
         DoubleNode<ItemType>* newNodePtr = new DoubleNode<ItemType>(nextItem);
         
         //Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);
         
         //Advance pointer to new last node
         newChainPtr = newChainPtr->getNext();
         //Link the current node to the previous one to create a doubly linked node
         newChainPtr->setPrevious(trailingPtr);
         //Advance the trailing pointer to get ready for the next link
         trailingPtr = trailingPtr->getNext();

         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }
      
      newChainPtr->setNext(nullptr); // Flag end of chain
   }
}  //End copy constructor

template<class ItemType>
DoublyLinkedList<ItemType>::~DoublyLinkedList()
{
   //clear();
}  // end destructor

/*
This insertion function inserts new nodes into the doubly linked list based on position
If a position specified is already occupied, the currently occupying node is moved one forward, and it's original position is replaced by the new node
*/
template<class ItemType>
bool DoublyLinkedList<ItemType>::insert(const ItemType& item, const int& position)
{
    //Two pointers are created to more easily create links
    DoubleNode<ItemType>* currentPtr = headPtr;
    DoubleNode<ItemType>* trailingPtr = headPtr;
    DoubleNode<ItemType>* newNodePtr = new DoubleNode<ItemType>();
    newNodePtr->setItem(item);
    int currentPosition = 2; //This variable will be used to keep track of how far along the pointers are in the link
    
    //This handles replacements for the head pointer if it's empty
    if (position == 1 && headPtr == nullptr) {
        headPtr = newNodePtr;
        itemCount++;
    //This does the same as above except it handles it when the head pointer is not empty
    } else if (position == 1 && headPtr != nullptr) {
        newNodePtr->setNext(currentPtr);
        currentPtr->setPrevious(newNodePtr);
        currentPtr = currentPtr->getPrevious();
        headPtr = currentPtr;
        itemCount++;
    } else {
        //This deals with replacements for all other positions
        currentPtr = currentPtr->getNext();
        while (currentPosition != position) {
            trailingPtr = trailingPtr->getNext();
            currentPtr = currentPtr->getNext();
            currentPosition++;
        }
        //If the position to be inserted is at the end of the link, this snippet of code deals with that
        if (currentPtr == nullptr) {
            trailingPtr->setNext(newNodePtr);
            newNodePtr->setPrevious(trailingPtr);
        } else {
        //Else, if it's somewhere in the middle, it defaults to this. This is where having two pointers to keep track of positioning become useful
            currentPtr->setPrevious(newNodePtr);
            newNodePtr->setNext(currentPtr);
            trailingPtr->setNext(newNodePtr);
            newNodePtr->setPrevious(trailingPtr);
        }
        itemCount++;
    }
    return true;
}  // end insert

/*
This function deals with removal of nodes in the link. It requires that the user specify a position to be removed
*/
template<class ItemType>
bool DoublyLinkedList<ItemType>:: remove(const int& position)
{
    //This deals with edge cases such as the user wanting to remove an index that does not exist
    if (position > itemCount || position < 1) {

        return false;
    }

    DoubleNode<ItemType>* currentPtr = headPtr->getNext();
    DoubleNode<ItemType>* trailingPtr = headPtr;
    int currentPosition = 2;
    //If the first index, which is the head pointer is to be removed, this is a special case. This snippet of code takes care of that by first unlinking the head, and tehn deleting the allocated memory
    if (position == 1) {

        currentPtr->setPrevious(nullptr);
        delete headPtr;
        headPtr = currentPtr;
        itemCount--;

    } else {
        //All other positions are handled by the following code
        while (currentPosition != position) {

            currentPtr = currentPtr->getNext();
            trailingPtr = trailingPtr->getNext();
            currentPosition++;
        }
        //After the positiont to be deleted is found, the following code checks to see if the position happens to be the last index. That is relatively easy to delete. It requires only unlinking the previous and next
        if (currentPtr->getNext() == nullptr) {

            currentPtr->setPrevious(nullptr);
            trailingPtr->setNext(nullptr);
            delete currentPtr; //Contents of pointer are deleted from memory
            itemCount--;

        } else if (currentPtr->getNext() != nullptr) {
        //Else, if the position to be deleted is in the middle somewhere, the process becomes more complicated, as there are 4 links to be severed, two next, and two previous.
            DoubleNode<ItemType>* leadingPtr = currentPtr->getNext();
            currentPtr->setNext(nullptr);
            currentPtr->setPrevious(nullptr);
            leadingPtr->setPrevious(trailingPtr);
            trailingPtr->setNext(leadingPtr);
            delete currentPtr; //Contents of pointer are deleted from memory
            itemCount--;

        }
    }

    return true;
}
/*
This method retrieves the size of the linked list
*/
template<class ItemType>
int DoublyLinkedList<ItemType>::getSize() const
{
    return itemCount;
}

/*
This method retrieves the head pointer of a linked list object. Comes in handy when accepting a linked list as an argument
*/
template<class ItemType>
DoubleNode<ItemType>* DoublyLinkedList<ItemType>::getHeadPtr() const
{
    return headPtr;
}

/*
This method retrieves the contents of a particular index in a linked list object. Position is used as a parameter
*/
template<class ItemType>
DoubleNode<ItemType>* DoublyLinkedList<ItemType>::getAtPos(const int& pos) const
{
    DoubleNode<ItemType>* currentPtr = headPtr;
    int currentPosition = 1;

    while (currentPosition != pos) {
        currentPtr = currentPtr->getNext();
        currentPosition++;
    }

    //cout<<currentPtr->getItem();
    return currentPtr;
}

/*
This method returns true or false on whether a linked list is empty
*/
template<class ItemType>
bool DoublyLinkedList<ItemType>::isEmpty() const
{
    if (itemCount == 0) {
        return true;
    } else {
        return false;
    }
}
/*
This method clears the entire linked list
*/
template<class ItemType>
void DoublyLinkedList<ItemType>::clear()
{
    //The strategy here is to delete the head pointer, and then push up the next index to become the new head, and deleting that as well. This continue until the contents of the list are reduced to zero
    DoubleNode<ItemType>* nodeToDeletePtr = headPtr;
    while (headPtr != nullptr)
    {
        headPtr = headPtr->getNext();

        // Return node to the system
        nodeToDeletePtr->setNext(nullptr);
        nodeToDeletePtr->setPrevious(nullptr);

        delete nodeToDeletePtr; //Deallocates the contents of this pointer from memory

        nodeToDeletePtr = headPtr;
    }  // end while

    itemCount = 0;
}
/*
This method displays the contents of the linked list in sequential order
*/
template<class ItemType>
void DoublyLinkedList<ItemType>::display() const
{
    DoubleNode<ItemType>* currentPtr = headPtr;

    while (currentPtr != nullptr) {
        cout<<currentPtr->getItem();
        currentPtr = currentPtr->getNext();
        if (currentPtr == nullptr) {
            cout<<'\n';
        } else {
            cout<<' ';
        }
    }

}

/*
This method displays the contents of the linked list starting from the last index
*/
template<class ItemType>
void DoublyLinkedList<ItemType>::displayBackwards() const
{
    DoubleNode<ItemType>* currentPtr = headPtr;

    while (currentPtr->getNext() != nullptr) {
        currentPtr = currentPtr->getNext();
    }

    while (currentPtr != nullptr) {
        cout<<currentPtr->getItem();
        currentPtr = currentPtr->getPrevious();
        if (currentPtr == nullptr) {
            cout<<'\n';
        } else {
            cout<<' ';
        }
    }

}
/*
This method takes two linked lists and combines them into one. Specifically, it takes each index in each list and interweaves them
Example: List1 = 1 -> 2 -> 3 -> 4
List2 = 5 -> 6 -> 7 -> 8
CombinedList = 1 -> 5 -> 2 -> 6 -> 3 -> 7 -> 4 -> 8
*/
template<class ItemType>
DoublyLinkedList<ItemType> DoublyLinkedList<ItemType>::interleave(const DoublyLinkedList<ItemType>& a_list)
{
    /*Two pointers for each list were created. The trailing pointers will be used to make the first connections
    while the current pointers will act as anchors so that the the nodes ahead of the ones being interwoven are not lost
    */
    int minIter = min(a_list.getSize(), itemCount); //This variable will be used for the for-loop below to set in place all of the indices up until the limits of the smaller list
    DoubleNode<ItemType>* a_listCurrentPtr = a_list.getHeadPtr();
    DoubleNode<ItemType>* originalListCurrentPtr = headPtr;

    DoublyLinkedList<ItemType> tempList; //An empty temporary list is created in order to hold the combined interwoven indices of the two lists provided
    
    for (int i = 1; i <= minIter; i++) { 

        tempList.insert(originalListCurrentPtr->getItem(), i*2 - 1); //The second parameter here uses a mathematical expression to ensure that each item in the first list are placed at every odd index
        tempList.insert(a_listCurrentPtr->getItem(), i*2); //This expression in the second parameter ensures the contents of the second list is placed at every even index
        originalListCurrentPtr = originalListCurrentPtr->getNext();
        a_listCurrentPtr = a_listCurrentPtr->getNext();

    }
    //From here on, the bigger list will have all of it's contents appended to the combined list
    int continueIndex = tempList.getSize() + 1; //This starts off from where the smaller list ended

    if (originalListCurrentPtr != nullptr) {
        while (originalListCurrentPtr != nullptr) {
            tempList.insert(originalListCurrentPtr->getItem(), continueIndex);
            originalListCurrentPtr = originalListCurrentPtr->getNext();
            continueIndex++;
        }        
    } else if (a_listCurrentPtr != nullptr) {
        while (a_listCurrentPtr != nullptr) {
            tempList.insert(a_listCurrentPtr->getItem(), continueIndex);
            a_listCurrentPtr = a_listCurrentPtr->getNext();
            continueIndex++;
        }        
    }
    //This returns the temporary list
    return tempList;
}