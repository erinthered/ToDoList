/**********************************************************************
Author:         Erin Williams
Date Created:   3/12/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Implementation File for Date Class
************************************************************************/
#include "date.h"
#include<iomanip>
#include<iostream>
#include<ostream>

namespace datewilliams {

Date& Date::operator =(const Date& rhs) {
    setMonth(rhs.getMonth());
    setDay(rhs.getDay());
    setYear(rhs.getYear());
    return *this;
}

std::ostream& operator <<(std::ostream& out, const Date& date) {
    out << std::setw(2) << std::setfill('0') << date.getMonth() << '/' << std::setw(2) << date.getDay() << '/' << date.getYear();
    return out;
}

bool Date::operator <(const Date& rhs) {
    if(year_ < rhs.year_) {
        return true;
    }
    else if(year_ == rhs.year_ && month_ < rhs.month_) {
        return true;
    }
    else if(year_ == rhs.year_ && month_ == rhs.month_ && day_ < rhs.day_) {
        return true;
    }
    else {
        return false;
    }
}

void Date::printMMDDYYYY(std::ostream& out) {
    out << std::setw(2) << std::setfill('0') << month_ << '/' << std::setw(2) << day_ << '/' << year_;
}

} //datewilliams
