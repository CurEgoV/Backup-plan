#include <iostream>
#include <string>
#include <list>
#include "order.h"

#ifndef CUSTOMER_H
#define CUSTOMER_H
using namespace std;

class Restaurant;

struct ContactInfo{
    string phoneNumber;
    string address;
};

class Customer
{
    private:
        string name;
        ContactInfo contactInf;
        int customerId;
        list<Order*> orders;
    public:
        Customer(string name, string phoneNumber, string 
        address);//customerId(nextCusId++)
        int get_id() const;
        void start_order(list<string>& orderItems, int resId, bool isDelivery);
        //creates a new object of Order class with given parameters
        void cancel_ord(int ordId);
        //if in_progress is true, cannot be cancelled. 
        //Else cancels order with given number
        void change_cnt_inf(const string& newNumber, const string&
        newAddress);
        //or could use ContactInfo& newcntinfo?
        OrderStatus get_status();
        void add_item_to_order(int ordId, const string& item);
        void remove_item_from_order(int ordId, const string& item);
        Order& get_order(int ordId);
        list<Order*> get_order_list() const;
        void pick_up_order(int ordId);
        void add_order(Order* order);

 
};

#endif 