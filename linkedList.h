/*************************************************************************
Title:          linkedList.h
Author:         Erin Williams
Date Created:   3/3/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Header File for Linked List Class
************************************************************************/

#ifndef __CS235_LINKEDLIST_H_
#define __CS235_LINKEDLIST_H_

#include<fstream>

namespace listwilliams {

template<class ItemType>
class LinkedList {
public:
    LinkedList();

    nodewilliams::Node<ItemType>* getHead() { return head_; }
    nodewilliams::Node<ItemType>* getTail() { return tail_; }
    void setHead(nodewilliams::Node<ItemType>* head) { head_ = head; }
    void setTail(nodewilliams::Node<ItemType>* tail) { tail_ = tail; }

    void incrementSize() { ++size_; } // to delete
    int size() { return size_; }
    bool empty() { return size_ > 0 ? false : true; }
    bool contains(const ItemType& data);
    int retrieve(int pos, ItemType& data); 

    void write(std::ostream& out);

    int insert(int pos, const ItemType& data);
    int push_front(const ItemType& data);
    int push_back(const ItemType& data);
     
private:
    nodewilliams::Node<ItemType> *head_, *tail_;
    int size_;

    nodewilliams::Node<ItemType>* findPos(const ItemType& data);
    int checkPos(const int& pos);
};

} //LinkedListWilliams

#include "linkedList.cpp"

#endif //__CS235_LINKEDLIST_H_
