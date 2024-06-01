#include "employee.h"

Employee::Employee (const string& n, double s, const Date& d){
    name = n;
    if (s>0.0)
        salary = s;
    else
        salary = 0.0;
    hireDate = d;
}
void Employee::print(){
    cout << name << "  $" << salary << "  " << hireDate << endl;
}
