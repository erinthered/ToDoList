/**********************************************************************
Title:          shoppingTask.h
Author:         Erin Williams
Date Created:   3/30/17
Class:          Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:      Aarsh Vora
Purpose:        Assignment #2
Description:    Header File for Shopping Task Class
************************************************************************/

#include<ostream>
#include<string>
#include<vector>
#include "date.h"
#include "task.h"

#ifndef __CS235_SHOPPINGTASK_H_
#define __CS235_SHOPPINGTASK_H_

namespace taskwilliams {

class ShoppingTask : public Task {
public:
    ShoppingTask(Date date, std::string description, std::vector<std::string> items) : Task(date, description), items_(items) {}

    inline std::vector<std::string> getItems() const { return items_; }
    inline void setItems(std::vector<std::string> items) { items_ = items; }

//    ShoppingTask& operator =(const ShoppingTask& rhs);
    inline bool operator ==(const ShoppingTask& rhs) { return getDescription() == rhs.getDescription() && getDate() == rhs.getDate() && items_ == rhs.items_; }
    inline bool operator !=(const ShoppingTask& rhs) { return getDescription() != rhs.getDescription() || getDate() != rhs.getDate() || items_ != rhs.items_; }

    friend std::ostream& operator <<(std::ostream& out, const ShoppingTask& task) {
        out << task.getDate() << " - " << task.getDescription();
        for(int i = 0; i < task.items_.size(); ++i) {
            out << task.items_[i];
        }
        out << std::endl;
        return out;
     }

private:
    std::vector<std::string> items_;
};

} //taskwilliams

#endif //__CS235_SHOPPINGTASK_H_
