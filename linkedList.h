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

#include<ostream>

namespace listwilliams {

template<class ItemType>
class LinkedList {
public:
    typedef nodewilliams::Node<ItemType> Node;

    LinkedList();
    ~LinkedList();

    Node* getHead() { return head_; }
    Node* getTail() { return tail_; }
    void setHead(Node* head) { head_ = head; }
    void setTail(Node* tail) { tail_ = tail; }

    int size() { return size_; }
    bool empty() { return size_ > 0 ? false : true; }
    bool contains(const ItemType& data);
    int retrieve(int pos, ItemType& data); 

    void write(std::ostream& out);

    int sortedInsert(const ItemType& data);
    int insert(int pos, const ItemType& data);
    int push_front(const ItemType& data);
    int push_back(const ItemType& data);

    int remove(const int& pos);
     
private:
    Node *head_, *tail_;
    int size_;

    Node* findPos(const ItemType& data);
    int checkPos(const int& pos);
};

} //LinkedListWilliams

#include "linkedList.cpp"

#endif //__CS235_LINKEDLIST_H_
