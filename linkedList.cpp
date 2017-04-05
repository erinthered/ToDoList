/*************************************************************************
Title:          linkedList.cpp
Author:         Erin Williams
Date Created:   3/3/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Implementation file for Doubly Linked List Class
*************************************************************************/

#ifndef __CS235_LINKEDLIST_CPP_
#define __CS235_LINKEDLIST_CPP_

#include "linkedList.h"
#include "node.h"

namespace listwilliams {

//Error codes used by checkPos() helper function
namespace {
    enum PositionCode { goodPosition = 0, negativePosition = -1, outOfBoundsPosition = -2 }; 
} // namespace

//Construct new doubly linked list of size zero with empty head and tail sentinal nodes
template<class ItemType>
LinkedList<ItemType>::LinkedList() : size_(0) {
    initializeSentinals();
 }

template<class ItemType>
LinkedList<ItemType>::~LinkedList() {
    clearList();
    delete head_;
    delete tail_;
}

//Deep copy constructor
template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& rhs) {
    initializeSentinals();
    size_ = 0;

    Node<ItemType>* current = rhs.head_->getNext();
    for(int i = 0; i < rhs.size(); ++i) {
        push_back(current->getData());
        current = current->getNext();
    }
}

template<class ItemType>
const LinkedList<ItemType>& LinkedList<ItemType>::operator =(const LinkedList<ItemType>& rhs) {
    if(this == &rhs) {
        return *this;
    }

    clearList();
    Node<ItemType>* current = rhs.head_->getNext();
    for(int i = 0; i < rhs.size(); ++i) {
        push_back(current->getData());
        current = current->getNext();
    }
    return *this;
}

//Find data in list, given position. Does error checking for valid position.
template<class ItemType>
int LinkedList<ItemType>::retrieve(int pos, ItemType& data) {
   if(checkPos(pos) == goodPosition) {
        Node<ItemType>* current = head_->getNext();
        for(int i = 0; i < pos; ++i) {
            current = current->getNext();
        }
        data = current->getData();
   }
   return checkPos(pos);  //Return error code -1 for negative position, -2 for out of bounds position
}

//Output all data in list
//Precondition: Operator << must be defined for ItemType
template<class ItemType>
void LinkedList<ItemType>::write(std::ostream& out) {
    Node<ItemType>* current = head_->getNext();
    for(int i = 0; i < size(); ++i) {
        out << current->getData() << std::endl;
        current = current->getNext();
    }
}

//Insert data to list such that data in previous node < data < data in next node
//Precondition: Operator < must be defined for ItemType
//Postcondition: Size is incremented, data is inserted such that data in previous
//node < data < data in next node
template<class ItemType>
int LinkedList<ItemType>::sortedInsert(const ItemType& data) {
    Node<ItemType>* current = head_->getNext();
    while(current != tail_ && current->getData() < data) {
            current = current->getNext();
     }
    Node<ItemType>* newNode = new Node<ItemType>;
    newNode->setData(data);
    newNode->setPrevious(current->getPrevious());
    newNode->setNext(current);
    current->getPrevious()->setNext(newNode);
    current->setPrevious(newNode);
    ++size_;
    return 0;
}

//Insert data to list at specific position
//Returns error code -1 if position given is negative, -2 if position is out of bounds.    
//Size of list is incremented.
template<class ItemType>
int LinkedList<ItemType>::insert(int pos, const ItemType& data) {
    if(checkPos(pos) == goodPosition) {
        Node<ItemType>* current = head_->getNext();
        
        for(int i = 0; i < pos; ++i) {
            current = current->getNext();
        }
        Node<ItemType>* newNode = new Node<ItemType>;
        newNode->setData(data);
        newNode->setPrevious(current->getPrevious());
        newNode->setNext(current);
        current->getPrevious()->setNext(newNode);
        current->setPrevious(newNode);
        ++size_;
        return 0;
    }
    return checkPos(pos);
}

//Remove data from specific position
//Returns error code -1 if position given is negative, -2 if position is out of bounds.
//Size of list is decremented
template<class ItemType>
int LinkedList<ItemType>::remove(int pos) {
    if(checkPos(pos) == goodPosition) {
        Node<ItemType>* current = head_->getNext();
       
        for(int i = 0; i < pos; ++i) {
            current = current->getNext();
        }
        current->getPrevious()->setNext(current->getNext());
        current->getNext()->setPrevious(current->getPrevious());

        delete current;
        --size_;
    } 
    return checkPos(pos);
}

//Add data to front of list
//Size of list is incremented
template<class ItemType>
int LinkedList<ItemType>::push_front(const ItemType& data) {
    insert(0, data);
    return 0;
}

//Add data to back of list
//Size of list is incremented
template<class ItemType>
int LinkedList<ItemType>::push_back(const ItemType& data) {
    insert(size(), data);
    return 0;
}

//Remove data from front of list
//Size of list is decremented
template<class ItemType>
int LinkedList<ItemType>::pop_front() {
    remove(0);
    return 0;
}

//Remove data from back of list
//Size of list is decremented
template<class ItemType>
int LinkedList<ItemType>::pop_back() {
    remove(size()-1);
    return 0;
}

//Remove all data from list
template<class ItemType>
int LinkedList<ItemType>::clearList() {
    while(!(empty())) {
        pop_front();
    }
    return 0;
}

//Intialize head and tail sentinal nodes
//Postcondition: head's next pointer points at tail, head's previous pointer
//points at NULL, tail's previous pointer points at head, tail's next pointer points at NULL.
template<class ItemType>
void LinkedList<ItemType>::initializeSentinals() {
    head_ = new Node<ItemType>;
    tail_ = new Node<ItemType>;
    head_->setNext(tail_);
    tail_->setPrevious(head_);
}

//Check that given position is not outside of the list
//Returns -1 if pos is a negative integer, -2 if pos > size of list,
//and 0 if position is a valid position in list
template<class ItemType>
int LinkedList<ItemType>::checkPos(int pos) {
    if(pos < 0) {
        return negativePosition;
    }
    else if (pos > size()) {
        return outOfBoundsPosition;
    }
    else {
        return goodPosition;
    }
}

//Finds the position of a node that contains the given data
template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getPos(const ItemType& data) {
    Node<ItemType>* current = head_->getNext();

     while(current != tail_) {
        if(current->getData() == data) {
            return current;
        }
        current = current->getNext();
    }
    return NULL;
} 

} //listwilliams 

#endif //__CS235_LINKEDLIST_CPP_
