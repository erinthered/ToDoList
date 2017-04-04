/**********************************************************************
Title:          eventTask.cpp
Author:         Erin Williams
Date Created:   3/30/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Implemenation File for Event Task Class
************************************************************************/

#include<string>
#include<ostream>
#include "eventTask.h"

namespace taskwilliams {

EventTask& EventTask::operator =(const EventTask& rhs) {
    description_ = rhs.description_;
    date_ = rhs.date_;
    location_ = rhs.location_;
    time_ = rhs.time_;
    return *this;
}

void EventTask::outputDetailed(std::ostream& out) {
    out << "\tWHERE: " << location_ << "\n" << "\tWHEN: " << time_ << "\n";
}
} //taskwilliams
