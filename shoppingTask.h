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
#include<fstream>
#include<string>
#include<vector>
#include "date.h"
#include "task.h"

#ifndef __CS235_SHOPPINGTASK_H_
#define __CS235_SHOPPINGTASK_H_

namespace taskwilliams {

class ShoppingTask : public Task {
public:
    ShoppingTask(Date date, std::string description, std::vector<std::string> items, std::string type = "S") : Task(date, description, type), items_(items) {}

    //Getters and setters for Task Class data members, also inherits all getters and setters from base Task class
    inline std::vector<std::string> getItems() const { return items_; }
    inline void setItems(std::vector<std::string> items) { items_ = items; }

    virtual ShoppingTask& operator =(const ShoppingTask& rhs);
    inline bool operator ==(const ShoppingTask& rhs) { return getDescription() == rhs.getDescription() && getDate() == rhs.getDate() && items_ == rhs.items_; }
    inline bool operator !=(const ShoppingTask& rhs) { return getDescription() != rhs.getDescription() || getDate() != rhs.getDate() || items_ != rhs.items_; }

    //Redefined virtual function to give output for Shopping Task class data member functions
    virtual void outputDetailed(std::ostream& out);
    //Redefined virtual function to give output for Shopping Task class data member functions in file specific format
    virtual void fileOutput(std::ofstream& out);

protected:
    std::vector<std::string> items_;  //Vector of items in shopping list
};

} //taskwilliams

#endif //__CS235_SHOPPINGTASK_H_
