**************************************************************************************
Title:              README.txt
Author:             Erin Williams
Date Created:       4/4/2017
Class:              Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:          Aarsh Vora
Purpose:            Assignment #2
Description:        Readme file for second project
***************************************************************************************

The makefile for this project compiles an executable, Project2, using the g++ compiler,
from the included .cpp files for the project. The make clean command is available.

All parts of this project are completed, nothing is incomplete.

The underlying data structure is a doubly linked list (and associated Node class containing
previous and next pointers as data members) with head and tail sentinal nodes to simplify 
the code and remove the need for special cases involving empty lists. There is also a Sorted 
Linked List class which includes a single data member consisting of a Linked List. The notable 
function is sorted insert which takes in the overloaded () operator (i.e. a functor) for 
comparing the Task classes (although any comparing functor could be written and used). The
doubly linked list is templated for its data input, and the sorted linked list class is 
templated for its data input and for a Comparator functor. The sorted insert function in the
sorted linked list class takes in data and a Comparator and iterates through the list from
head->next until either the end of the list is reached (tail) or an node is found that 
contains data that is greater than the data to insert. In the first case, the data is the
largest element in the list and is inserted before tail, in the second case, the data is
set to a new node that is inserted before the node in which the data that is larger is found.

The linked list class has an enum outlining error codes for the function that checks a valid position.
The linked list class contains a copy constructor and an overloaded = operator that both make deep copies
of the list. The destructor clears the list and then deletes the sentinal head and tail nodes. There are 
a few functions in the linked list class that are not used in this project, notably a basic write function
and a basic sorted insert function. I wrote these as an exercise and decided to leave them, as they add
functionality and modularity to the list, even if I didn't use them for this project. They were also 
useful for testing purposes. We've discussed the algortithms for the functions in a linked list class
pretty exensively, but because my implementation of a linked list is a doubly linked list with head and
tail sentinal nodes, I was able to skip the special head and tail cases for many functions, as well as the
empty list cases. Having a head node that does not contain data also meant that I needed to start all iterations
through the list from head->next, instead of from head directly.

There is a Task Class that is used both to create objects of the Generic Task type and as a base class
for three other Task classes that inherit from this class, Shopping Task, Homework Task, and Event Task.
These classes use virtual functions to take advantage of polymorphism in the print and output functions,
which each output the data members that are unique to each type of Task class. Each Task class contains 
or inherits a data member of the Date Class. The Date Class is a simple class that contains three
ints for month, day, and year and functions for processing those ints, notably a function that outputs
the date formatted in MM/DD/YYYY format and an overloaded < operator function for comparing objects of
Date type in the Driver class. 

The Driver class has many functions for processing Tasks, as well as a functor for comparing Tasks. It adds, 
completes, saves, and loads lists of tasks, which use the Sorted Linked List class to store a list of 
pointers to the different Task classes. A quick breakdown of the relevant algorithms of the functions of the
Driver class:

getDateInput: A helper function that converts user input of the form MM/DD/YYYY into integers that can be
stored in the Date class's data members. Works by getting assigning each variable month, day, year to a 
substring that is the characters of the string up to the next / character, then removing the characters 
that have been processed and the first / of the substring. The year variable gets the remainder of the 
string. These values are then converted to integers.

addTask: Gets user input and assigns it to the data members of the task classes. For classes other than
the Generic Task class, the data members unique to that class are added dependant on the Task type 
chosen by the user. 

printTasks: Iterates through a non-empty list, producing a numbered, ordered list of the current tasks
in the specified list. If DETAILED is entered as input by the user, the outputDetailed function is called
for the specified Task class, ensuring that the unique data members for that class will appear in the
output.

deleteTask: Gets the number of the task to be removed from the list by calling the Sorted Linked List's
remove function, which calls the Linked List class's remove function. Notably, this is called on the 
input + 1, as the linked list is ordered from 0 and the outputted list is ordered from 1.

completeTask: Checks for valid user input and calls the Sorted Linked List class's retrieve function
(which calls the Linked List class's retrieve function), takes the retrieved data and inserts it 
to the Completed Task list, then removes the data from the outstanding task list. Also called on 
pos-1, as above.

saveTasks: Gets a file name from the user as input and iterates through a non-empty outstanding tasks list,
adding each data member from each Task in the list followed by a | character.

loadTasks: Gets a file name from the user as input, checks that the specified file was opened successfully,
and calls the STL getline function up to the next | character for each data item for each Task, then pushes
the Task to the back of the list using the Sorted Linked List class's push_back function (which uses the 
Linked List class's push_back function. The tricky part of this function was adding all tasks in the vector
of shopping items in the Shopping Task class. This was done by getting the entire remaining line of all items 
as a string, and processing the string using the find_first_of function from the STL to get the end of the next
substring and a begin variable to find the end of the substring. Each substring is then pushed to the vector.
as a substring until the end of the string is reached.
