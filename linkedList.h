/***********************************************************************
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
#include "node.h"

namespace listwilliams {

template<class ItemType>
class LinkedList {
public:

    typedef Node<ItemType> Node;

    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList<ItemType>& rhs);
    const LinkedList<ItemType>& operator =(const LinkedList<ItemType>& rhs);

    //Getters and Setters
    inline Node* getHead() const { return head_; }
    inline Node* getTail() const { return tail_; }
    inline void setHead(Node* head) { head_ = head; }
    inline void setTail(Node* tail) { tail_ = tail; }

    inline int size() const { return size_; }
    inline void incrementSize() { ++size_; }
    inline bool empty() const { return size() == 0; }

    //Returns true if data is found in list, false if not found
    bool contains (const ItemType& data) { return getPos(data) != NULL; }
    //Function variable data contains value of data at position pos if
    //data is found in list, returns error code if not found.
    int retrieve(int pos, ItemType& data);

    void write(std::ostream& out);  
 //   template<class ItemType, typename Comparator>            
 //   int sortedComparatorInsert(const ItemType& data, Comparator isLessThan);
    int sortedInsert(const ItemType& data);
    int insert(int pos, const ItemType& data);  

    int remove(int pos);                        

    int push_front(const ItemType& data);      
    int push_back(const ItemType& data);       

    int pop_front();                           
    int pop_back();                            

    int clearList();                            

private:
    Node *head_, *tail_;
    int size_;

    Node* getPos(const ItemType& data);
    int checkPos(int pos);                     
    void initializeSentinals();               
};

} //LinkedListWilliams

#include "linkedList.cpp"

#endif //__CS235_LINKEDLIST_H_
