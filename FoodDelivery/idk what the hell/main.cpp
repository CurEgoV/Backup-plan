#include "manager.h"

ostream$ operator<< (ostream& o, const Employee & e){
    o << e.name << "  $" << e.salary << "  " << e.hireDate << endl;
    return o;
}

ostream& operator<< (ostream& o, const Date& d){
    o << d,day << "/" << d.month << "/" << d.year;
    return o;
}

int main(){
    Date hireDateForJack (1, 3, 2005);
    Manager manager ("Bob Manager", 120000.0, hireDateForJack);
    Date emptyDate;
    Employee jack ("Jack", 100000.0, hireDateForJack);
    Employee emptyEmployee ("Empty", 0.0, emptyDate);
    emptyEmployee = jack;
    Employee copyEmployee = emptyEmployee;
    cout << "Jack is: " << jack;
    cout << "empty: " << emptyEmployee;
    cout << "copy: " << copyEmployee;


    cout << "Manager is: " << manager;

    cout << endl << endl;
    jack.print();
    Employee *eptr;
    eptr = &manager;
    cout << eptr->print() << " for manager" << endl;
    Manager *mptr;
    mptr = &manager;
    cout << "mptr->print();" << endl;
    mptr->print();
    eptr = mptr;
    mptr = (Manager*) eptr;
    Employee& empref = manager;
    cout << "empref.print();" << endl;
    empref.print();
    manager.setBonus(500);
    empref.print();
}