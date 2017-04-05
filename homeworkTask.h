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

    inline std::string getCourse() const { return course_; }
    inline void setCourse(std::string course) { course_ = course; }

    virtual HomeworkTask& operator =(const HomeworkTask& rhs);
    virtual inline bool operator ==(const HomeworkTask& rhs) { return getDescription() == rhs.getDescription() && getDate() == rhs.getDate() && course_ == rhs.course_; }
    virtual inline bool operator !=(const HomeworkTask& rhs) { return getDescription() != rhs.getDescription() || getDate() != rhs.getDate() || course_ != rhs.course_; }

    virtual void outputDetailed(std::ostream& out);
    virtual void fileOutput(std::ofstream& out) { out << "|" << course_ << "\n"; }

//    friend std::ostream& operator <<(std::ostream& out, const HomeworkTask& task) {
//        out << task.getDate() << " - " << task.getDescription() << " - " << task.course_ << std::endl;
//        return out;
 //    }

protected:
    std::string course_;

};

} //taskwilliams

#endif //__CS235_HOMEWORKTASK_H_
