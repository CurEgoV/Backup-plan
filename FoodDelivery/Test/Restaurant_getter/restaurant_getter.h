#ifndef RESTAURANT_GETTER_H
#define RESTAURANT_GETTER_H

#include <list>
#include "restaurant.h"

Restaurant& get_restaurant(int resId);
Restaurant& get_restaurant(const string& res_name);

#endif
