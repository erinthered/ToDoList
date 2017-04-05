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
#include<fstream>
#include<sstream>
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
void addTask(SortedLinkedList<Task*, Comparator>& list);
void printTasks(SortedLinkedList<Task*, Comparator> list, std::string printType);
void printFormattedDate(Task* task);
void deleteTask(SortedLinkedList<Task*, Comparator>& list);
void completeTask(SortedLinkedList<Task*, Comparator>& list, SortedLinkedList<Task*, Comparator>& completed);
void saveTasks(SortedLinkedList<Task*, Comparator>& list);
int loadTasks(SortedLinkedList<Task*, Comparator>& list);

int main() {

	SortedLinkedList<Task*, Comparator> toDoList;            //List of current Tasks
	SortedLinkedList<Task*, Comparator> completedTasks;      //List of completed Tasks
	std::string command;

	std::cout << "Welcome to the To-Do List." << std::endl;

	do {
		std::cout << "Please enter a command, or type HELP for a full list of commands." << std::endl;
		std::cin >> command;

		if(command == "ADD") {
			addTask(toDoList);
		}
		else if(command == "PRINT" || command == "DETAILED") {
			printTasks(toDoList, command);
		}
		else if(command == "REMOVE") {
                       deleteTask(toDoList);    
                }
		else if(command == "COMPLETE") {
	               completeTask(toDoList, completedTasks); 
		}
		else if(command == "COMPLETED") {
                       printTasks(completedTasks, command);			
		}
		else if(command == "SAVE") {
			saveTasks(toDoList);
		}
		else if(command == "LOAD") {
			loadTasks(toDoList);
		}
		else if(command == "HELP") {
			std::cout << "Please choose one of the following options: \n";
			std::cout << "ADD - Add a new Task\n";
			std::cout << "PRINT - Display all Tasks in order of Due Date\n";
			std::cout << "DETAILED - Display all Tasks in Detailed format\n";
			std::cout << "REMOVE - Delete a Task\n";
			std::cout << "COMPLETE - Mark a Task as Completed\n";
			std::cout << "COMPLETED - Display all completed Tasks\n";
			std::cout << "SAVE - Save all Tasks to a specified File\n";
			std::cout << "LOAD - Load all Tasks from a File\n";
			std::cout << "EXIT - Exit Program\n";
		}
		else if(command == "EXIT") {
			//Do nothing
		}
		else {
			std::cout << "I didn't understand that command.\n";
		}
	} while(command != "EXIT");
	return 0;
}

int loadTasks(SortedLinkedList<Task*, Comparator>& list) {
    Date date;
    std::string filename, taskType, fileline, line, description, dateString;
    char delimiter = '|';;
    std::ifstream file;

    std::cout << "What file would you like to load outstanding tasks from?\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, filename);   
    file.open(filename);
 
    if(file) {
        list.clearList();
        while(!file.eof()) {

            getline(file, taskType, delimiter);
            getline(file, dateString, delimiter);
            date = getDateInput(dateString);
        //Load general task
            if(taskType == "G") {
               getline(file, description);
               Task* newTask = new Task(date, description);
               list.push_back(newTask);
            } 
            else {
                getline(file, description, delimiter); 
                //Load shopping task      
                if(taskType == "S") {
                   std::vector<std::string> shoppingList1;
                   //Get list of shopping items
                   getline(file, line);
                   std::string item;
                   std::string::size_type found = line.find_last_of(delimiter);
                   while(found != std::string::npos) {
                       item = line.substr(found + 1);
                       shoppingList1.push_back(item);
                       line = line.substr(0, found);
                       found = line.find_last_of(delimiter);
                   }
                   item = line;
                   shoppingList1.push_back(item);
                   std::vector<std::string> shoppingList;
                   for(int i = shoppingList1.size(); i > 0; --i) {
                       shoppingList.push_back(shoppingList1[1]);
                    }
 
                   ShoppingTask* shopping = new ShoppingTask(date, description, shoppingList);
                   list.push_back(shopping);
                } 
                //Load Event Task
                if(taskType == "E") {
                    std::string location, time;
                    getline(file, location, delimiter);
                    getline(file, time);                  
 
                    EventTask* event = new EventTask(date, description, location, time);
                    list.push_back(event);
                 }
                 //Load Homework Task
                 if(taskType == "H") {
                     std::string course;
                     getline(file, course);
                     HomeworkTask* homework = new HomeworkTask(date, description, course);
                     list.push_back(homework);

                 }
            }
        }
        file.close();
        return 0;
    }
    else {
        return -1;
    }       
}

void saveTasks(SortedLinkedList<Task*, Comparator>& list) { 
    if(list.empty()) {
        std::cout << "You have no outstanding tasks!\n";
    }
    std::string filename;
    std::ofstream out;
    std::cout << "Where would you like to save your outstanding tasks?\n";
    std::cin >> filename;
    out.open(filename);
    
    Node<Task*>* current = list.getHead()->getNext();
    for(int i = 0; i < list.size(); ++i) {
            out << current->getData()->getType() << "|";
            current->getData()->getDate().printMMDDYYYY(out);
            out << "|" << current->getData()->getDescription();
            current->getData()->fileOutput(out);
            current = current->getNext();
    }
    out.close();    
}


void completeTask(SortedLinkedList<Task*, Comparator>& list, SortedLinkedList<Task*, Comparator>& completed) {
    if(list.empty()) {
        std::cout << "You have no outstanding tasks!\n";
    }
    else {
        int pos;
        std::cout << "Which task would you like to complete?\n";
        std::cin >> pos;
        while (pos < 0 || pos > list.size()) {
            std::cout << "That was not a valid number. Please try again.\n";
            std::cout << "Which task would you like to complete?\n";
            std::cin >> pos;
        }
        Task* toComplete;
        list.getList().retrieve(pos-1, toComplete);
        completed.sortedComparatorInsert(toComplete, Comparator());
        list.remove(pos-1);
        std::cout << "Task marked complete successfully.\n";
    }
}

void deleteTask(SortedLinkedList<Task*, Comparator>& list) {
        if(list.empty()) {
            std::cout << "You have no outstanding tasks!\n";
        }
        else {
            int pos;
            std::cout << "Which task would you like to remove?\n";
            std::cin >> pos;
            while(pos < 0 || pos > list.size()) {
                std::cout << "That was not a valid number. Please try again.\n";
                std::cout << "Which task would you like to remove?\n";
                std::cin >> pos;
            }
            list.remove(pos-1);
        }
}

void printTasks(SortedLinkedList<Task*, Comparator> list, std::string printType) {
	Task* current;
	if(list.empty()) {
		std::cout << "You have no outstanding tasks!\n";
		return;
	}
	for(int i = 0; i < list.size(); ++i) {
		std::cout << i+1 << ". ";

		list.getList().retrieve(i, current);
		printFormattedDate(current);
		std::cout << " - ";

		if(current->getType() == "E") {
			std::cout << "[Event] ";
		}
		if(current->getType() == "H") {
			std::cout << "[Homework] ";
		}
		if(current->getType() == "S") {
			std::cout << "[Shopping] ";
		}
                
                std::cout << current->getDescription();

                std::cout << std::endl;
                if(printType == "DETAILED") {
                    current->outputDetailed(std::cout);
                }
	}
}

void printFormattedDate(Task* task) {
	std::cout << std::setw(2) << std::setfill('0') << task->getDate().getMonth() << '/' << std::setw(2) << task->getDate().getDay() << '/' << task->getDate().getYear();
}

void addTask(SortedLinkedList<Task*, Comparator>& list) {
	std::string type;
	Date date;
	std::string dateString, description;

	std::cout << "What type of task is this? [G: Generic, S: Shopping, E: Event, H: Homework]\n";
	std::cin >> type;

	while(type != "G" && type != "S" && type != "E" && type != "H") {
		std::cout << "That was not a valid response. Please enter one of the following choices: " << std::endl;
		std::cout << "[G: Generic, S: Shopping, E: Event, H: Homework]\n";
		std::cin >> type;
	}

	std::cout << "When is this task due?\n";
	std::cin >> dateString;
	date = getDateInput(dateString); 

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "How would you describe this task?\n";
	std::getline(std::cin, description);

	if(type == "G") {
		Task* task = new Task(date, description);
		list.sortedComparatorInsert(task, Comparator());
	}
	else if(type == "S") {
		std::vector<std::string> itemList;
		std::string input;

		std::cout << "What items do you need to buy?";
		std::cout << " [Type your item and press ENTER to add another item. Type DONE to complete the list.]";
		std::cout << std::endl;

		while(input != "DONE") {
			std::getline(std::cin, input);
                        if(input != "DONE") {
			    itemList.push_back(input);
                        }
		}
		ShoppingTask* shopping = new ShoppingTask(date, description, itemList);
		list.sortedComparatorInsert(shopping, Comparator());
	}
	else if(type == "E") {
		std::string location, time;

		std::cout << "Where is this event taking place?\n";
		std::getline(std::cin, location);
		std::cout << "When is this event taking place?\n";
		std::cin >> time;

		EventTask* event = new EventTask(date, description, location, time);
		list.sortedComparatorInsert(event, Comparator());
	}
	else if(type == "H") {
		std::string course;

		std::cout << "What subject is this homework task for?\n";
		std::getline(std::cin, course);

		HomeworkTask* homework = new HomeworkTask(date, description, course);
		list.sortedComparatorInsert(homework, Comparator());
	}
        std::cout << "Task added successfully.\n";
}                  

Date getDateInput(std::string input) {
	Date date;
	std::string month, day, year;
	std::string delimiter = "/";

	month = input.substr(0, input.find(delimiter));
	input.erase(0, input.find(delimiter) + delimiter.length());
	day = input.substr(0, input.find(delimiter));
	input.erase(0, input.find(delimiter) + delimiter.length());
	year = input;

	date.setMonth(std::stoi(month.c_str()));
	date.setDay(std::stoi(day.c_str()));
	date.setYear(std::stoi(year.c_str()));

	return date;
}
