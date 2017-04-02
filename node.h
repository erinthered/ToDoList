/*************************************************************************
Title:          node.h
Author:         Erin Williams
Date Created:   3/3/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Node Class for a doubly linked list
**************************************************************************/
#ifndef __CS235_NODE_H_
#define __CS235_NODE_H_

#include<cstddef>

namespace listwilliams {

template<class ItemType>
class Node {
public:

    Node() : previous_(NULL), next_(NULL) {}

    ItemType getData( ) const { return data_; }
    Node* getPrevious() const { return previous_; }
    Node* getNext() const { return next_; }
    void setData(ItemType data) { data_ = data; }
    void setPrevious(Node* prev) { previous_ = prev; }
    void setNext(Node* next) { next_ = next; }

private:
 
    ItemType data_;
    Node* previous_; //Pointer to previous Node
    Node* next_;     //Pointer to next Node
};

} //listwilliams

#include "node.cpp"

#endif //__CS235_NODE_H
