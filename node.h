/*************************************************************************
Title:          node.h
Author:         Erin Williams
Date Created:   3/3/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Node for Linked List Class
**************************************************************************/
#ifndef __CS235_NODE_H_
#define __CS235_NODE_H_

namespace nodewilliams {

template<class ItemType>
class Node {
public:

    Node(const ItemType& data, Node* next) : data_(data), next_(next) {};

    ItemType getData( ) const { return data_; }
    Node* getNext() const { return next_; }
    void setData(ItemType dataIn) { data_ = dataIn; }
    void setNext(Node* nextIn) { next_ = nextIn; }

private:
 
    ItemType data_;
    Node* next_;     //Pointer to next Node
};

} //nodewilliams

#endif //__CS235_NODE_H
