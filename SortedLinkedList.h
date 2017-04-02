/***********************************************************************
Title:          sortedLinkedList.h
Author:         Erin Williams
Date Created:   3/3/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Header File for Linked List Class
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

    inline int getList() const { return list_; }

    int sortedComparatorInsert(const ItemType& data, Comparator isLessThan);

private:
    LinkedList<ItemType> list_;
};

} //LinkedListWilliams

#include "SortedLinkedList.cpp"

#endif //__CS235_SORTEDLINKEDLIST_H_
