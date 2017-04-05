/*************************************************************************
Title:          sortedLinkedList.cpp
Author:         Erin Williams
Date Created:   3/3/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Implementation file for Linked List Class
*************************************************************************/

#ifndef __CS235_SORTEDLINKEDLIST_CPP_
#define __CS235_SORTEDLINKEDLIST_CPP_

#include "SortedLinkedList.h"
#include "linkedList.h"
#include "node.h"

namespace listwilliams {

//Insert data to list such that data at previous < data < data at next
//Precondition: ItemType has a defined Comparator operator () that determines relative value of ItemType class.
//Postcondition: data is inserted in list such that data at previous < data < data at next, as defined by Comparator.
template<class ItemType, typename Comparator>
int SortedLinkedList<ItemType, Comparator>::sortedComparatorInsert(const ItemType& data, Comparator isLessThan) {
    Node<ItemType>* current = list_.getHead()->getNext();
    while(current != list_.getTail() && isLessThan(current->getData(), data)) {
            current = current->getNext();
     }
    Node<ItemType>* newNode = new Node<ItemType>;
    newNode->setData(data);
    newNode->setPrevious(current->getPrevious());
    newNode->setNext(current);
    current->getPrevious()->setNext(newNode);
    current->setPrevious(newNode);
    list_.incrementSize();
    return 0;
}

} //listwilliams 

#endif //__CS235_LINKEDLIST_CPP_
