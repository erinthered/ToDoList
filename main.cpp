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
#include<string>
#include<string.h>
#include "node.h"
#include "linkedList.h"
#include "SortedLinkedList.h"
#include "date.h"
#include "task.h"
#include "homeworkTask.h"
#include "shoppingTask.h"
#include "eventTask.h"

using namespace listwilliams;
using namespace datewilliams;
using namespace taskwilliams;

struct Comparator {
    bool operator ()(Task* lhs, Task* rhs) const {
        if(lhs->getDate() != rhs->getDate()) {
            return lhs->getDate() < rhs->getDate();
        }
        else {
            return strcmp(lhs->getDescription().c_str(), rhs->getDescription().c_str()) < 0;
        }
    }
};

Date getDateInput(std::string input);
int addTask(SortedLinkedList<Task*, Comparator> list, Comparator comp);
int addSpecificTaskType(SortedLinkedList<Task*, Comparator> list, char type, std::string description, Date date, Comparator comp);

int main() {

    SortedLinkedList<Task*, Comparator> toDoList;            //List of current Tasks
    SortedLinkedList<Task*, Comparator> completedTasks;      //List of completed Tasks
    Comparator isLessThan;

    std::cout << "Welcome to the To-Do List." << std::endl;
    std::cout << "Please enter a command, or type HELP for a full list of commands." << std::endl;
    std::string command;
    std::cin >> command;

    if(command == "ADD") {
        addTask(toDoList, isLessThan);
    }

    return 0;
}

int addTask(SortedLinkedList<Task*, Comparator>& list, Comparator comp) {
    char type;
    Date date;
    std::string dateString, description;

    std::cout << "What type of task is this? [G: Generic, S: Shopping, E: Event, H: Homework]";
    std::cin >> type;
    while(type != 'G' || type != 'S' || type != 'E' || type != 'H') {
        std::cout << "That was not a valid response. Please enter one of the following choices:" << std::endl;
        std::cout << "[G: Generic, S: Shopping, E: Event, H: Homework]";
        std::cin >> type;
    }

    std::cout << "When is this task due?";
    std::cin >> dateString;
    date = getDateInput(dateString); 

    std::cout << "How would you describe this task?";
    std::cin >> description;

    int success = addSpecificTaskType(list, type, description, date, comp);
    return success;
}

int addSpecificTaskType(SortedLinkedList<Task*, Comparator>& list, char type, std::string description, Date date, Comparator comp) {
        if(type == 'G') {
            Task* task = new Task(date, description);
            list.sortedComparatorInsert(task, comp);
            return 0;
        }
        else if(type == 'S') {
            std::vector<std::string> itemList;
            std::string input;

            std::cout << "What items do you need to buy?";
            std::cout << " [Type your item and press ENTER to add another item. Type DONE to complete the list.]";
            std::cout << std::endl;

            while(input != "DONE") {
                std::cin >> input;
                itemList.push_back(input);
            }
            ShoppingTask* shopping = new ShoppingTask(date, description, itemList);
            list.sortedComparatorInsert(shopping, comp);
            return 0;
        }
        else if(type == 'E') {
            std::string location, time;
                
            std::cout << "Where is this event taking place?";
            std::cin >> location;
            std::cout << "When is this event taking place?";
            std::cin >> time;

            EventTask* event = new EventTask(date, description, location, time);
            list.sortedComparatorInsert(event, comp);
            return 0;
        }
        else if(type == 'H') {
            std::string course;

            std::cout << "What subject is this homework task for?";
            std::cin >> course;

            HomeworkTask* homework = new HomeworkTask(date, description, course);
            list.sortedComparatorInsert(homework, comp);
            return 0;
        }
        else {
            return -1;
        }
 }                  

Date getDateInput(std::string input) {
    Date date;
    std::string month, day, year;
    int intMonth, intDay, intYear;
    int i = 0;

    while(input[i] != '/') {
        month = month + input[i];
        ++i;
    }
    while(input[i] != '/') {
        day = day + input[i];
        ++i;
    }
    while(i < input.length()) {
        year = year + input[i];
        ++i;
    }     
    
    intMonth = std::stoi(month);
    intDay = std::stoi(day);
    intYear = std::stoi(year);

    date.setMonth(intMonth);
    date.setDay(intDay);
    date.setYear(intYear);

    return date;
}
