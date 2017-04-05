/***********************************************************************
Title:          linkedList.h
Author:         Erin Williams
Date Created:   3/3/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Header File for Doubly Linked List Class with head and
                tail sentinal nodes
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
    //Postcondition: parameter data contains data at position if found.
    int retrieve(int pos, ItemType& data);

    //Outputs all data in list
    //Precondition: Operator >> must be defined for ItemType
    void write(std::ostream& out);
    //Inserts data in linked list such that data in previous node < data in node < data in next node
    //Precondition: Operator < must be defined for ItemType
    //Postcondition: data is inserted such that data in previous node < data in node < data in next node
    int sortedInsert(const ItemType& data);
    //Inserts data in list at specified position in list
    //Returns error code if position is out of bounds
    int insert(int pos, const ItemType& data);  

    //Remove data in specified position
    //Returns error code if position is out of bounds
    int remove(int pos);                        

    //Insert data to front of list
    int push_front(const ItemType& data);
    //Insert data to back of list        
    int push_back(const ItemType& data);       

    //Remove data from front of list
    int pop_front();
    //Remove data from back of list                           
    int pop_back();                            

    //Clear contents of list
    //Postcondition: List consists of head and tail sentinal nodes and has size 0
    int clearList();                            

private:
    Node *head_, *tail_;
    int size_;

    Node* getPos(const ItemType& data);  //Find position of data - helper function
    int checkPos(int pos);               //Check for valid position taken as input - helper function
    void initializeSentinals();          //Initializes head and tail sentinals - helper function
};

} //LinkedListWilliams

#include "linkedList.cpp"

#endif //__CS235_LINKEDLIST_H_
