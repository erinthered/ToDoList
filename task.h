/**********************************************************************
Title:          task.h
Author:         Erin Williams
Date Created:   3/27/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Header File for Generic Task Class
************************************************************************/

#include<ostream>
#include<string>
#include "date.h"

#ifndef __CS235_TASK_H_
#define __CS235_TASK_H_

namespace taskwilliams {

class Task {
public:
    typedef datewilliams::Date Date;

    Task(Date date, std::string description) : date_(date), description_(description) {}

    inline std::string getDescription() const { return description_; }
    inline Date getDate() const { return date_; }
    inline void setDescription(std::string description) { description_ = description; } 
    inline void setDate(int month, int day, int year) { date_.setMonth(month); date_.setDay(day); date_.setYear(year); }

//    Task& operator =(const Task& rhs);
    inline bool operator ==(const Task& rhs) { return description_ == rhs.description_ && date_ == rhs.date_; }
    inline bool operator !=(const Task& rhs) { return description_ != rhs.description_ || date_ != rhs.date_; }
   
//Need to write print and detailed print functions? Or just do this in main 
    friend std::ostream& operator <<(std::ostream& out, const Task& task) { 
        out << task.date_ << " - " << task.description_ << std::endl;
        return out;
     }     

private:
    Date date_;
    std::string description_;

};

} //taskwilliams

#endif //__CS235_TASK_H_
