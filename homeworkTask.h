/**********************************************************************
Title:          homeworkTask.h
Author:         Erin Williams
Date Created:   3/30/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Header File for Homework Task Class
************************************************************************/

#include<ostream>
#include<string>
#include<fstream>
#include "date.h"
#include "task.h"

#ifndef __CS235_HOMEWORKTASK_H_
#define __CS235_HOMEWORKTASK_H_

namespace taskwilliams {

class HomeworkTask : public Task {
public:
    HomeworkTask(Date date, std::string description, std::string course, std::string type = "H") : Task(date, description, type), course_(course) {}

    //Getters and setters for course data members, inherits all base Task class getters and setters
    inline std::string getCourse() const { return course_; }
    inline void setCourse(std::string course) { course_ = course; }

    virtual HomeworkTask& operator =(const HomeworkTask& rhs);
    virtual inline bool operator ==(const HomeworkTask& rhs) { return getDescription() == rhs.getDescription() && getDate() == rhs.getDate() && course_ == rhs.course_; }
    virtual inline bool operator !=(const HomeworkTask& rhs) { return getDescription() != rhs.getDescription() || getDate() != rhs.getDate() || course_ != rhs.course_; }

    //Redefined virtual function to give output for Homework Task class data member functions
    virtual void outputDetailed(std::ostream& out);
    //Redefined virtual function to give output for Homework Task class data member functions in file output specific format
    virtual void fileOutput(std::ofstream& out) { out << "|" << course_ << "\n"; }

protected:
    std::string course_;

};

} //taskwilliams

#endif //__CS235_HOMEWORKTASK_H_
