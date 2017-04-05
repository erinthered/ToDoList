/**********************************************************************
Title:          task.h
Author:         Erin Williams
Date Created:   3/27/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Header File for Generic Task Class
                This is the Base Class for all other Task Classes
************************************************************************/

#include<ostream>
#include<fstream>
#include<string>
#include "date.h"

#ifndef __CS235_TASK_H_
#define __CS235_TASK_H_

namespace taskwilliams {

class Task {
public:
    typedef datewilliams::Date Date;

    Task(Date date, std::string description, std::string type = "G") : date_(date), description_(description), type_(type) {}
    ~Task() {};
   
    //Getters and setters 
    inline std::string getDescription() const { return description_; }
    inline Date getDate() const { return date_; }
    inline std::string getType() const { return type_; }
    inline void setDescription(std::string description) { description_ = description; } 
    inline void setDate(int month, int day, int year) { date_.setMonth(month); date_.setDay(day); date_.setYear(year); }
    inline void setDate(Date date) { date_ = date; }
    inline void setType(std::string type) { type_ = type; }

    virtual Task& operator =(const Task& rhs);
    virtual inline bool operator ==(const Task& rhs) { return getDescription() == rhs.getDescription() && getDate() == rhs.getDate(); }
    virtual inline bool operator !=(const Task& rhs) { return getDescription() != rhs.getDescription() || getDate() != rhs.getDate(); }
  
    //Virtual function to give output for Generic Task class data member functions
    virtual void outputDetailed(std::ostream& out) {} 
    //Virtual function to give output for Generic Task class data member functions in file specific format
    virtual void fileOutput(std::ofstream& out) { out << "\n"; }

protected:
    Date date_;
    std::string description_;
    std::string type_;
};

} //taskwilliams

#endif //__CS235_TASK_H_
