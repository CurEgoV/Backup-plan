#include "manager.h"

void Manager::print(){
    Employee::print();
    cout << "bonus=" << bonus << endl;
}

bool Manager::setBonus(double x){
    if (x <0.0)
        return false;
    bonus = x;
    return true;
}
