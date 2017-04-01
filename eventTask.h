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
#include<string>
#include "date.h"
#include "task.h"

#ifndef __CS235_EVENTTASK_H_
#define __CS235_EVENTTASK_H_

namespace taskwilliams {

class EventTask : public Task {
public:
    EventTask(Date date, std::string description, std::string location, std::string time) : Task(date, description), location_(location), time_(time) {}

    inline std::string getLocation() const { return location_; }
    inline void setLocation(std::string location) { location_ = location; }
    inline std::string getTime() const { return time_; }
    inline void setTime(std::string time) { time_ = time; }

//    EventTask& operator =(const EventTask& rhs);
    inline bool operator ==(const EventTask& rhs) { return getDescription() == rhs.getDescription() && getDate() == rhs.getDate() && location_ == rhs.location_ && time_ == rhs.time_; }
    inline bool operator !=(const EventTask& rhs) { return getDescription() != rhs.getDescription() || getDate() != rhs.getDate() || location_ != rhs.location_ || time_ != rhs.time_; }

    friend std::ostream& operator <<(std::ostream& out, const EventTask& task) {
        out << task.getDate() << " - " << task.getDescription() << task.location_ << task.time_ << std::endl;
        return out;
     }

private:
    std::string location_;
    std::string time_;
};

} //taskwilliams

#endif //__CS235_EVENTTASK_H_
