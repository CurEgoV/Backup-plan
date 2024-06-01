#include <iostream>
#include <string>
#include <list>
#include "order.h"
#include <memory>

#ifndef CUSTOMER_H
#define CUSTOMER_H

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
        list<shared_ptr<Order>> orders;
    public:
        Customer(string name, string phoneNumber, string 
        address);
        int get_id() const;
        const string& get_name() const;
        void start_order(const list<string>& orderItems, int resId, bool isDelivery);
        //creates a new object of Order class with given parameters
        void cancel_ord(int ordId);
        //if in_progress is true, cannot be cancelled. 
        //Else cancels order with given number
        void change_cnt_inf(const string& newNumber, const string&
        newAddress);
        void add_item_to_order(int ordId, const string& item);
        void remove_item_from_order(int ordId, const string& item);
        Order& get_order(int ordId);
        list<shared_ptr<Order>> get_order_list() const { return orders; }
        void pick_up_order(int ordId);
        void add_order(shared_ptr<Order> order);


};



#endif 