/*************************************************************************
Title:          main.cpp
Author:         Erin Williams
Date Created:   3/3/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-6:50pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Main file for ToDo List Project
**************************************************************************/

#include<iostream>
#include<assert.h>
#include "node.h"
#include "linkedList.h"
using namespace nodewilliams;
using namespace listwilliams;

int main() {

LinkedList<int> myList = LinkedList<int>();
assert(myList.empty());

myList.push_front(1);
myList.push_back(3);
myList.insert(1, 2);

assert(myList.size() == 3);

myList.write(std::cout);

assert(myList.contains(3));
std::cout << "contained\n";

int myData;
myList.retrieve(1, myData);
std::cout << myData << std::endl;
assert(myData == 2);
std::cout << "Retrieved\n";

myList.push_front(10);
myList.push_back(4);
assert(myList.getTail()->getData() == 4);

myList.write(std::cout);

std::cout << "Size is: " << myList.size() << std:: endl;

return 0;

}
