#include <iostream>
using namespace std;

#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

class Date {
private:
    int day;
    int month;
    int year;
public:
    Date (int,int,int);
    Date();
    void setDate (int, int, int);
    int getDay();
    int getMonth();
    int getYear();
    friend ostream& operator<< (ostream&, const Date&);
};

#endif //DATE_H_INCLUDED