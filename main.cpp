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
//#include<stdlib.h>
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

//Comparator for Task Classes. Left task is < right task if the date is earlier.
//If the date is the same, left task is < right task if the description is 
//alphabetically < the description of the right task.
struct Comparator {
	bool operator ()(Task* lhs, Task* rhs) const {     
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

//Gets Date as a string, converts to three ints (month, day, year) for processing and storage.
//Returns an object of Date class
//Precondition: User input is in the form MM/DD/YYYY
//Postcondition: User input has been converted to an object of Date class
Date getDateInput(std::string input);

//Add a task to the ToDo List.
//Postcondition: Task has been added in sorted order such that previous Task < Task < next Task   *************CHECK THIS************
void addTask(SortedLinkedList<Task*, Comparator>& list);

//Print all tasks in ToDo List to the console in sorted order (see Comparator struct for sorting details)
void printTasks(SortedLinkedList<Task*, Comparator> list, std::string printType);
//Helper function that takes in the date data from a task object and formats it in MM/DD/YYYY format.
void printFormattedDate(Task* task);

//Remove a task from the ToDo List
void deleteTask(SortedLinkedList<Task*, Comparator>& list);

//Remove a task from the ToDo List and add it to the Completed Task List.
void completeTask(SortedLinkedList<Task*, Comparator>& list, SortedLinkedList<Task*, Comparator>& completed);

//Saves tasks to a file given as user input
void saveTasks(SortedLinkedList<Task*, Comparator>& list);
//Loads tasks from a file given as user input
void loadTasks(SortedLinkedList<Task*, Comparator>& list);

//Helper function that returns true if list is empty and prints a message to the user.
//Returns false if the list contains one or more tasks.
bool isEmpty(SortedLinkedList<Task*, Comparator> list);

int main() {

	SortedLinkedList<Task*, Comparator> toDoList;            //List of current Tasks
	SortedLinkedList<Task*, Comparator> completedTasks;      //List of completed Tasks
	std::string command;                                     //input

	std::cout << "Welcome to the To-Do List." << std::endl;

	do {    //while cammand is not EXIT, get input
		std::cout << "Please enter a command, or type HELP for a full list of commands." << std::endl;
		std::getline(std::cin, command);

		if(command == "ADD") {
			addTask(toDoList);                                    //Add to ToDoList
		}
		else if(command == "PRINT" || command == "DETAILED") {
			printTasks(toDoList, command);                        //Print to console, regular or detailed
		}
		else if(command == "REMOVE") {
                       deleteTask(toDoList);                                  //Remove task from list 
                }
		else if(command == "COMPLETE") {
	               completeTask(toDoList, completedTasks);                //Add task to Completed List
		}
		else if(command == "COMPLETED") {
                       printTasks(completedTasks, command);	              //Print Completed List to console	
		}
		else if(command == "SAVE") {
			saveTasks(toDoList);                                  //Save outstanding tasks to specified file
		}
		else if(command == "LOAD") {
			loadTasks(toDoList);                                  //Load outstanding tasks from specified file
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
			std::cout << "Thank you for using To-Do List!\n";
		}
		else {
			std::cout << "I didn't understand that command.\n";
		}
	} while(command != "EXIT");
	return 0;
}

//Load tasks from file given as user input to outstanding task list
//Postcondition: outstanding ToDo list contains all Tasks loaded from specified file.
//and all existing tasks before loading are deleted.
//Print error message to console if file fails to open and load fails.
void loadTasks(SortedLinkedList<Task*, Comparator>& list) {
    Date date;
    std::string filename, taskType, line, description, dateString;
    char delimiter = '|';   //Tasks loaded with | character deliminations
    std::ifstream file;

    //Open file taken as input.
    std::cout << "What file would you like to load outstanding tasks from?\n";
    getline(std::cin, filename);   
    file.open(filename);
 
    if(file) {
        list.clearList();                            //clear any existing files from list
        while(!file.eof()) {

            getline(file, taskType, delimiter);      //get tasktype
            getline(file, dateString, delimiter);    //get Date as string
            date = getDateInput(dateString);         //Convert Date to Date object

            //Load general task
            if(taskType == "G") {
               getline(file, description);           //get task description
               Task* newTask = new Task(date, description);
               list.push_back(newTask);
            } 
            else {
                getline(file, description, delimiter); //get task description
                //Load shopping task      
                if(taskType == "S") {
                   std::vector<std::string> shoppingList;
                   //Get list of shopping items
                   getline(file, line);                                            //get entire line of shopping items as single line.
                   std::string item;
                   std::string::size_type begin = 0;                               //beginning of line
                   std::string::size_type found = line.find_first_of(delimiter);   //find first instance of | char in line
                   while(found != std::string::npos) {                             //while the end of the line is not reached
                       item = line.substr(begin, (found - begin));                 //item is substring between begin and number of chars between found & begin
                       shoppingList.push_back(item);                               //push to vector
                       begin = found + 1;                                          //advance begin to next section
                       found = line.find_first_of(delimiter, begin);               //find next instance of | char in line
                   }
                   item = line.substr(begin, (found - begin));                     //add final item;
                   shoppingList.push_back(item);
 
                   ShoppingTask* shopping = new ShoppingTask(date, description, shoppingList);
                   list.push_back(shopping);
                } 
                //Load Event Task
                if(taskType == "E") {
                    std::string location, time;
                    getline(file, location, delimiter);  //get event task location
                    getline(file, time);                 //get event task time
 
                    EventTask* event = new EventTask(date, description, location, time);
                    list.push_back(event);
                 }
                 //Load Homework Task
                 if(taskType == "H") {
                     std::string course;
                     getline(file, course);             //get homework task course
                     HomeworkTask* homework = new HomeworkTask(date, description, course);
                     list.push_back(homework);

                 }
            }
        }
        file.close();
        std::cout << "Tasks loaded successfully!\n";
    }
    else {
        std::cout << "File failed to load. Please try again.\n";
    }       
}

//Save ToDo List to file name given as input by user
//Postcondition: file contains saved Sorted Linked List of Tasks separated
//by newline characters. Each data item in each line is separated by a | character.
void saveTasks(SortedLinkedList<Task*, Comparator>& list) { 
    if(!isEmpty(list)) {             //Check for empty list
        std::string filename;
        std::ofstream out;
        std::cout << "Where would you like to save your outstanding tasks?\n";
        std::getline(std::cin, filename);
        out.open(filename);
   
        if(out) {
            //Iterate through Sorted Linked List - ToDo List of outstanding tasks. Add task data on one line, separated by
            //'|' characters, followed by '\n' character
            Node<Task*>* current = list.getHead()->getNext();
            for(int i = 0; i < list.size(); ++i) {
                out << current->getData()->getType() << "|";  
                current->getData()->getDate().printMMDDYYYY(out);
                out << "|" << current->getData()->getDescription();
                current->getData()->fileOutput(out);
                current = current->getNext();
            }
            out.close();
            std::cout << "Tasks saved successfully!\n";
        }   
        else {
            std::cout << "File failed to load. Please try again.\n";
        }
    }
}

//Remove tasks from outstanding ToDo List and add to Completed List
void completeTask(SortedLinkedList<Task*, Comparator>& list, SortedLinkedList<Task*, Comparator>& completed) {
    if(!isEmpty(list)) {                                              //Check for empty list
        int pos;
        std::string stringPos;
        std::cout << "Which task would you like to complete?\n";
        std::getline(std::cin, stringPos);
        pos = atoi(stringPos.c_str());                               //convert string input to int value

        while (pos < 0 || pos > list.size()) {                       //Check for valid input
            std::cout << "That was not a valid number. Please try again.\n";
            std::cout << "Which task would you like to complete?\n";
            std::getline(std::cin, stringPos);
            pos = atoi(stringPos.c_str());                          //convert string input to int value
        }
        Task* toComplete;
        list.getList().retrieve(pos-1, toComplete);                 //Find task
        completed.sortedComparatorInsert(toComplete, Comparator()); //insert task node to Completed List
        list.remove(pos-1);                                         //Remove task from ToDo List
        std::cout << "Task marked complete successfully.\n";
    }
}

void deleteTask(SortedLinkedList<Task*, Comparator>& list) {
        if(!isEmpty(list)) {                                        //Check for empty list
            std::string stringPos;
            int pos;
            std::cout << "Which task would you like to remove?\n";
            std::getline(std::cin, stringPos);
            pos = atoi(stringPos.c_str());                          //Convert string input to int value

            while(pos < 0 || pos > list.size()) {                   //Check for valid input
                std::cout << "That was not a valid number. Please try again.\n";
                std::cout << "Which task would you like to remove?\n";
                std::getline(std::cin, stringPos);
                pos = atoi(stringPos.c_str());                      //convert string input to int value
            }
            list.remove(pos-1);                                     //Remove task
            std::cout << "Task removed successfully.\n";
         }
}

void printTasks(SortedLinkedList<Task*, Comparator> list, std::string printType) {
         if(!isEmpty(list)) {
             Node<Task*>* current = list.getHead()->getNext();           //start at beginning of list
             for(int i = 0; i < list.size(); ++i) {
                 std::cout << i+1 << ". ";
                 current->getData()->getDate().printMMDDYYYY(std::cout);  //print formatted date
                 std::cout << " - ";

                 if(current->getData()->getType() == "E") {
                         std::cout << "[Event] ";
                 }
                 if(current->getData()->getType() == "H") {
                         std::cout << "[Homework] ";
                 }
                 if(current->getData()->getType() == "S") {
                         std::cout << "[Shopping] ";
                 }
                 std::cout << current->getData()->getDescription() << std::endl;  //get current Task description
      
                 //Print detailed output for different task classes         
                 if(printType == "DETAILED") {
                     current->getData()->outputDetailed(std::cout);
                 }

                 current = current->getNext();                             //advance iteration
            }
	}
}

//Print Date object in MM/DD/YYYY format
void printFormattedDate(Task* task) {
	std::cout << std::setw(2) << std::setfill('0') << task->getDate().getMonth() << '/' << std::setw(2) << task->getDate().getDay() << '/' << task->getDate().getYear();
}

//Add task to a sorted linked list
//Postcondition: Task is inserted in List such that the previous Task < Task < the next Task.
void addTask(SortedLinkedList<Task*, Comparator>& list) {
	Date date;
	std::string type, dateString, description;

	std::cout << "What type of task is this? [G: Generic, S: Shopping, E: Event, H: Homework]\n";
	std::getline(std::cin, type);                                        //Task

	while(type != "G" && type != "S" && type != "E" && type != "H") {    //check input
		std::cout << "That was not a valid response. Please enter one of the following choices: " << std::endl;
		std::cout << "[G: Generic, S: Shopping, E: Event, H: Homework]\n";
		std::getline(std::cin, type);
	}

	std::cout << "When is this task due?\n";
	std::getline(std::cin, dateString);                                 //Date
	date = getDateInput(dateString);                                    //Convert date to standard format

	std::cout << "How would you describe this task?\n";
	std::getline(std::cin, description);                                //Description

        //Insert Generic Task to list
	if(type == "G") {
		Task* task = new Task(date, description);
		list.sortedComparatorInsert(task, Comparator());            
	}
        //Insert Shopping Task to list
	else if(type == "S") {
                //Insert shopping items to vector based on user input
		std::vector<std::string> itemList;
		std::string input;

		std::cout << "What items do you need to buy?";     //***************CHECK THIS OUTPUT*************
		std::cout << " [Type your item and press ENTER to add another item. Type DONE to complete the list.]\n";

		while(input != "DONE") {
			std::getline(std::cin, input);
                        if(input != "DONE") {
			    itemList.push_back(input);
                        }
		}
		ShoppingTask* shopping = new ShoppingTask(date, description, itemList);
		list.sortedComparatorInsert(shopping, Comparator());
	}
        //Insert Event Task to list
	else if(type == "E") {
		std::string location, time;

		std::cout << "Where is this event taking place?\n";
		std::getline(std::cin, location);                            //Location
		std::cout << "When is this event taking place?\n";
		std::getline(std::cin,time);                                 //Time

		EventTask* event = new EventTask(date, description, location, time);
		list.sortedComparatorInsert(event, Comparator());
	}
        //Insert Homework Task to list
	else if(type == "H") {
		std::string course;                                           

		std::cout << "What subject is this homework task for?\n";
		std::getline(std::cin, course);                               //Course

		HomeworkTask* homework = new HomeworkTask(date, description, course);
		list.sortedComparatorInsert(homework, Comparator());
	}
        std::cout << "Task added successfully.\n";
}
                  
        /******FIX ME*******AND ADD OUTPUT MESSAGES THAT ARE MISSING*************************************/


//Converts user input in form MM/DD/YYYY to integer variables to be used as Date class data members
//Returns input converted to an object of Date class
//Preconditon: User intput is a string in the form MM/DD/YYYY
//Postcondition: Input is converted to an object of Date class
Date getDateInput(std::string input) {
	Date date;
	std::string month, day, year;
	std::string delimiter = "/";

	month = input.substr(0, input.find(delimiter));             //get month
	input.erase(0, input.find(delimiter) + delimiter.length()); //remove month and / characters from string
	day = input.substr(0, input.find(delimiter));               //get day
	input.erase(0, input.find(delimiter) + delimiter.length()); //remove day and / characters from string
	year = input;                                               //get year

	date.setMonth(std::stoi(month.c_str()));                    //convert month to int
	date.setDay(std::stoi(day.c_str()));                        //convert day to int
	date.setYear(std::stoi(year.c_str()));                      //convert year to int

	return date;
}

//Check for an empty list - helper function
//Returns true if list is empty and outputs message
//Returns false if list contains Tasks
bool isEmpty(SortedLinkedList<Task*, Comparator> list) {
    if(list.empty()) {
       std::cout << "You have no outstanding tasks!\n";
       return true;
    }
    else {
        return false;
    }
 }
