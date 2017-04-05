/**********************************************************************
Title:          task.cpp
Author:         Erin Williams
Date Created:   3/27/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Implemenation File for Generic Task Class
************************************************************************/

#include<string>
#include "task.h"

namespace taskwilliams {

Task& Task::operator =(const Task& rhs) {
    description_ = rhs.description_;
    date_ = rhs.date_;
    return *this;
}

} //taskwilliams
