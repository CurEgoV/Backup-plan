#include "employee.h"

#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

class Manager: public Employee
{
private:
    double bonus;
public:
    Manager(string n, double s, const Date& d): Employee(n, s, d){
    bonus = 0;
    }
    bool setBonus(double);
    double getBonus();
    virtual void print();
};

#endif