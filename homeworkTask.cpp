/**********************************************************************
Title:          homeworkTask.cpp
Author:         Erin Williams
Date Created:   3/30/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Implemenation File for Homework Task Class
************************************************************************/

#include<string>
#include<ostream>
#include "homeworkTask.h"

namespace taskwilliams {

HomeworkTask& HomeworkTask::operator =(const HomeworkTask& rhs) {
    description_ = rhs.description_;
    date_ = rhs.date_;
    course_ = rhs.course_;
    return *this;
}

//Redefined virtual function to give output for Homework Task class data member functions
void HomeworkTask::outputDetailed(std::ostream& out) {
    out << "    SUBJECT: " << course_ << "\n";
}

} //taskwilliams
