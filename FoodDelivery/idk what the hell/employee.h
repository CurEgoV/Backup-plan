#include <iostream>
using namespace std;
#include "date.h"

#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INLCUDED

class Employee{
private:
    string name;
    double salary;
    Date hireDate;
protected:

public:
    Employee (const string&, double, const Date&);
    void setName(const string&);
    bool setSalary(double);
    void setHireDate (const Date&);
    string getName();
    double getSalary();
    Date getHireDate();
    friend ostream& operator<< (ostream&, const Employee&);
    virtual void print();
};

#endif