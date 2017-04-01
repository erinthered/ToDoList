/*************************************************************************
Title:          sortedLinkedList.cpp
Author:         Erin Williams
Date Created:   3/3/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Implementation file for Linked List Class
*************************************************************************/

#ifndef __CS235_LINKEDLIST_CPP_
#define __CS235_LINKEDLIST_CPP_

#include "SortedLinkedList.h"
#include "node.h"

namespace listwilliams {

namespace {
    enum PositionCode { goodPosition = 0, negativePosition = -1, outOfBoundsPosition = -2 }; 
} // namespace

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

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& rhs) {
    initializeSentinals();
    size_ = 0;

    Node* current = rhs.head_->getNext();
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
    Node* current = rhs.head_->getNext();
    for(int i = 0; i < rhs.size(); ++i) {
        push_back(current->getData());
        current = current->getNext();
    }
    return *this;
}

template<class ItemType>
int LinkedList<ItemType>::retrieve(int pos, ItemType& data) {
   if(checkPos(pos) == goodPosition) {
        Node* current = head_->getNext();
        for(int i = 0; i < pos; ++i) {
            current = current->getNext();
        }
        data = current->getData();
   }
   return checkPos(pos);
}

template<class ItemType>
void LinkedList<ItemType>::write(std::ostream& out) {
    Node* current = head_->getNext();
    for(int i = 0; i < size(); ++i) {
        out << current->getData() << std::endl;
        current = current->getNext();
    }
}

template<class ItemType, typename Comparator>
int LinkedList<ItemType>::sortedComparatorInsert(const ItemType& data, Comparator isLessThan) {
    Node* current = head_->getNext();
    while(current != tail_ && isLessThan(current->getData(), data)) {
            current = current->getNext();
     }
    Node* newNode = new Node;
    newNode->setData(data);
    newNode->setPrevious(current->getPrevious());
    newNode->setNext(current);
    current->getPrevious()->setNext(newNode);
    current->setPrevious(newNode);
    ++size_;
    return 0;
}
 
template<class ItemType>
int LinkedList<ItemType>::sortedInsert(const ItemType& data) {
    Node* current = head_->getNext();
    while(current != tail_ && current->getData() < data) {
            current = current->getNext();
     }
    Node* newNode = new Node;
    newNode->setData(data);
    newNode->setPrevious(current->getPrevious());
    newNode->setNext(current);
    current->getPrevious()->setNext(newNode);
    current->setPrevious(newNode);
    ++size_;
    return 0;
}
    
template<class ItemType>
int LinkedList<ItemType>::insert(int pos, const ItemType& data) {
    if(checkPos(pos) == goodPosition) {
        Node* current = head_->getNext();
        
        for(int i = 0; i < pos; ++i) {
            current = current->getNext();
        }
        Node* newNode = new Node;
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

template<class ItemType>
int LinkedList<ItemType>::remove(int pos) {
    if(checkPos(pos) == goodPosition) {
        Node* current = head_->getNext();
       
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
int LinkedList<ItemType>::pop_front() {
    remove(0);
    return 0;
}

template<class ItemType>
int LinkedList<ItemType>::pop_back() {
    remove(size()-1);
    return 0;
}

template<class ItemType>
int LinkedList<ItemType>::clearList() {
    while(!(empty())) {
        pop_front();
    }
    return 0;
}

template<class ItemType>
void LinkedList<ItemType>::initializeSentinals() {
    head_ = new Node;
    tail_ = new Node;
    head_->setNext(tail_);
    tail_->setPrevious(head_);
}

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

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getPos(const ItemType& data) {
    Node* current = head_->getNext();

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
