/*************************************************************************
Title:          driver.h
Author:         Erin Williams
Date Created:   3/3/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-6:50pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Driver header file for ToDo List Project
 **************************************************************************/

#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include "node.h"
#include "linkedList.h"
#include "SortedLinkedList.h"
#include "date.h"
#include "task.h"
#include "homeworkTask.h"
#include "shoppingTask.h"
#include "eventTask.h"

#ifndef __CS235_DRIVER_H_
#define __CS235_DRIVER_H_

namespace tododriverwilliams {
class Driver {
public:

    //Comparator for Task Classes. Left task is < right task if the date is earlier.
    //If the date is the same, left task is < right task if the description is
    //alphabetically < the description of the right task.
    struct Comparator {
            bool operator ()(taskwilliams::Task* lhs, taskwilliams::Task* rhs) const {
                    if(lhs->getDate() != rhs->getDate()) {
                            //Compare dates using overloaded Date < operator.
                            return lhs->getDate() < rhs->getDate();
                    }
                    else {
                            //Compare string values using string compare
                            return strcmp(lhs->getDescription().c_str(), rhs->getDescription().c_str()) < 0;
                    }
            }
    };

    //Driver function for ToDoList
    //Gets input from the user and performs the specified tasks on a sorted linked list of outstanding tasks and a
    //sorted linked list of completed tasks. Can add tasks to a list, remove tasks, print tasks in regular or detailed
    //format, mark tasks as completed (move to completed list), print list of completed tasks, save current todo list to
    //a specified file, and load tasks to the current todo list from a specified file (deleting any existing tasks). The
    //user can print a list of possible commands to the screen by typing HELP.
    void run();

    //Gets Date as a string, converts to three ints (month, day, year) for processing and storage.
    //Returns an object of Date class
    //Precondition: User input is in the form MM/DD/YYYY
    //Postcondition: User input has been converted to an object of Date class
    datewilliams::Date getDateInput(std::string input);

    //Add a task to the ToDo List.
    //Postcondition: Task has been added in sorted order such that previous Task < Task < next Task   *************CHECK THIS************
    void addTask(listwilliams::SortedLinkedList<taskwilliams::Task*, Comparator>& list);

    //Print all tasks in ToDo List to the console in sorted order (see Comparator struct for sorting details)
    void printTasks(listwilliams::SortedLinkedList<taskwilliams::Task*, Comparator> list, std::string printType);
    //Helper function that takes in the date data from a task object and formats it in MM/DD/YYYY format.
    void printFormattedDate(taskwilliams::Task* task);

    //Remove a task from the ToDo List
    void deleteTask(listwilliams::SortedLinkedList<taskwilliams::Task*, Comparator>& list);

    //Remove a task from the ToDo List and add it to the Completed Task List.
    void completeTask(listwilliams::SortedLinkedList<taskwilliams::Task*, Comparator>& list, listwilliams::SortedLinkedList<taskwilliams::Task*, Comparator>& completed);

    //Saves tasks to a file given as user input
    void saveTasks(listwilliams::SortedLinkedList<taskwilliams::Task*, Comparator>& list);
    //Loads tasks from a file given as user input
    void loadTasks(listwilliams::SortedLinkedList<taskwilliams::Task*, Comparator>& list);

    //Helper function that returns true if list is empty and prints a message to the user.
    //Returns false if the list contains one or more tasks.
    bool isEmpty(listwilliams::SortedLinkedList<taskwilliams::Task*, Comparator> list);
};

} //tododriverwilliams

#endif //__CS235_DRIVER_H_
