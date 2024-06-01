#include "date.h"

Date::Date (int d, int m, int y){
    day = d;
    month = m;
    year = y;
};

Date::Date(){
    day = 0;
    month = 0;
    year = 0;
};