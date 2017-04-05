/***********************************************************************
Title:          sortedLinkedList.h
Author:         Erin Williams
Date Created:   3/3/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Header File for Sorted Linked List Class, which contains
                a doubly linked list
************************************************************************/

#ifndef __CS235_SORTEDLINKEDLIST_H_
#define __CS235_SORTEDLINKEDLIST_H_

#include<ostream>
#include "node.h"
#include "linkedList.h"

namespace listwilliams {

template<class ItemType, typename Comparator>
class SortedLinkedList {
public:
    //Getters and setters
    inline LinkedList<ItemType> getList() const { return list_; }
    inline int size() { return list_.size(); }
    inline bool empty() { return list_.empty(); }
    inline Node<ItemType>* getHead() { return list_.getHead(); }
    inline Node<ItemType>* getTail() { return list_.getTail(); }

    //Clear all data from list
    //Postcondition: list consists of head and tail sentinal nodes and has size 0.
    void clearList() { list_.clearList(); }

    //Remove data from list at given position, decrement size
    void remove(int pos) { list_.remove(pos); }

    //Adds data to end of list
    void push_back(const ItemType& data) { list_.push_back(data); }

    //Insert data to list such that data at previous < data < data at next
    //Precondition: ItemType has a defined Comparator operator () that determines
    //relative value of ItemType class.
    //Postcondition: data is inserted in list such that data at previous <
    //data < data at next, as defined by Comparator.
    int sortedComparatorInsert(const ItemType& data, Comparator isLessThan);

private:
    LinkedList<ItemType> list_;
};

} //LinkedListWilliams

#include "SortedLinkedList.cpp"

#endif //__CS235_SORTEDLINKEDLIST_H_
