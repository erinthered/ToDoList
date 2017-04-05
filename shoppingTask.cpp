/**********************************************************************
Title:          shoppingTask.cpp
Author:         Erin Williams
Date Created:   3/30/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Implemenation File for Shopping Task Class
************************************************************************/

#include<string>
#include<fstream>
#include "shoppingTask.h"

namespace taskwilliams {

ShoppingTask& ShoppingTask::operator =(const ShoppingTask& rhs) {
    description_ = rhs.description_;
    date_ = rhs.date_;
    items_ = rhs.items_;
    return *this;
}

void ShoppingTask::outputDetailed(std::ostream& out) {
    out << "\tITEMS TO PURCHASE: \n";
    for(int i = 0; i < items_.size(); ++i) {
        out << "\t" << items_[i] << "\n";
    }
}

void ShoppingTask::fileOutput(std::ofstream& out) {
    for(int i = 0; i < items_.size(); ++i) {
        out << "|" << items_[i];
    }
    out << "\n";
}

} //taskwilliams
