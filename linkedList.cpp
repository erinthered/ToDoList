/*************************************************************************
Title:          linkedList.cpp
Author:         Erin Williams
Date Created:   3/3/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Implementation file for Linked List Class
*************************************************************************/

#ifndef __CS235_LINKEDLIST_CPP_
#define __CS235_LINKEDLIST_CPP_

#include "linkedList.h"

namespace listwilliams {

template<class ItemType>
LinkedList<ItemType>::LinkedList() : head_(NULL), tail_(NULL), size_(0) {}

template<class ItemType>
LinkedList<ItemType>::~LinkedList() {
    while(size_ > 0) {
        remove(0);
    }
}

template<class ItemType> 
void LinkedList<ItemType>::write(std::ostream& out) {
//    nodewilliams::Node<ItemType>* current = getHead();
    nodePtr current = getHead();
    while(current != NULL) {
        out << current->getData() << std::endl;
        current = current->getNext();
    }
}

template<class ItemType>
bool LinkedList<ItemType>::contains(const ItemType& data) {
    return findPos(data) != NULL;
}

template<class ItemType>
int LinkedList<ItemType>::retrieve(int pos, ItemType& data) {
   if(checkPos(pos) == 0) {
       nodePtr current = getHead();
//       nodewilliams::Node<ItemType>* current = getHead();
       for(int i = 0; i < pos; ++i) {
           current = current->getNext();
       }
       data = current->getData();
    }
    return checkPos(pos);
} 
           
template<class ItemType>
nodewilliams::Node<ItemType>* LinkedList<ItemType>::findPos(const ItemType& data) {
    nodewilliams::Node<ItemType>* current = getHead();
    while(current != NULL) {
        if(current->getData() == data) {
            return current;
        }
        current = current->getNext();
    }
    return NULL;
}

template<class ItemType>
int LinkedList<ItemType>::insert(int pos, const ItemType& data) {
    if(checkPos(pos) == 0) {
        nodewilliams::Node<ItemType>* newNode = new nodewilliams::Node<ItemType>(data, NULL);
        nodewilliams::Node<ItemType>* temp = head_;
        if(head_ == NULL) {
            head_ = tail_ = newNode;
        }
        else if(pos == 0) {
            newNode->setNext(head_);
            head_ = newNode;
        }
        else if(pos == size_) {
            tail_->setNext(newNode);
            tail_ = newNode;
        }
        else {
            for(int i = 0; i < (pos-1); ++i) {
                temp = temp->getNext();
            }
            newNode->setNext(temp->getNext());
            temp->setNext(newNode);
        }
        ++size_;
    }
    return checkPos(pos);
}

template<class ItemType>
int LinkedList<ItemType>::push_front(const ItemType& data) {
    insert(0, data);
    return 0;
}

template<class ItemType>
int LinkedList<ItemType>::push_back(const ItemType& data) {
    insert(size(), data);
    return 0;
}

template<class ItemType>
int LinkedList<ItemType>::remove(const int& pos) {
    if(head_ == NULL) {
        return -3;
    }
    if(checkPos(pos) == 0) {
        nodewilliams::Node<ItemType>* toDelete = head_;
        nodewilliams::Node<ItemType>* temp = head_;
        if(pos == 0) {
            head_ = toDelete->getNext();
        }
        else {
            for(int i = 0; i < (pos -1); ++i) {
                temp = temp->getNext();
            }
            toDelete = temp->getNext();
            temp->setNext(toDelete->getNext());
        }
        toDelete->setNext(NULL);
        delete toDelete;
        toDelete = NULL;
        size_--;
    }

    return checkPos(pos); 
}

template<class ItemType>
int LinkedList<ItemType>::checkPos(const int& pos) {
    if(pos < 0) {
        return -1;
    }
    if (pos > size()) {
        return -2;
    }
    return 0;
} 

} //listwilliams 

#endif //__CS235_LINKEDLIST_CPP_
