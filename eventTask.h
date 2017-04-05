/**********************************************************************
Title:          eventTask.h
Author:         Erin Williams
Date Created:   3/30/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Header File for Event Task Class
************************************************************************/

#include<ostream>
#include<fstream>
#include<string>
#include "date.h"
#include "task.h"

#ifndef __CS235_EVENTTASK_H_
#define __CS235_EVENTTASK_H_

namespace taskwilliams {

class EventTask : public Task {
public:
    EventTask(Date date, std::string description, std::string location, std::string time, std::string type = "E") : Task(date, description, type), location_(location), time_(time) {}

    //Getters and setters for Event Task data members, also inherits base Task class getters and setters
    inline std::string getLocation() const { return location_; }
    inline void setLocation(std::string location) { location_ = location; }
    inline std::string getTime() const { return time_; }
    inline void setTime(std::string time) { time_ = time; }

    virtual EventTask& operator =(const EventTask& rhs);
    virtual inline bool operator ==(const EventTask& rhs) { return getDescription() == rhs.getDescription() && getDate() == rhs.getDate() && location_ == rhs.location_ && time_ == rhs.time_; }
    virtual inline bool operator !=(const EventTask& rhs) { return getDescription() != rhs.getDescription() || getDate() != rhs.getDate() || location_ != rhs.location_ || time_ != rhs.time_; }

    //Redefined virtual function to give output for Event Task class data member functions
    virtual void outputDetailed(std::ostream& out);
    //Redefined virtual function to give output for Event Task class data member functions in file specific format
    virtual void fileOutput(std::ofstream& out) { out << "|" << location_ << "|" << time_ << "\n"; }
    
protected:
    std::string location_;
    std::string time_;
};

} //taskwilliams

#endif //__CS235_EVENTTASK_H_
