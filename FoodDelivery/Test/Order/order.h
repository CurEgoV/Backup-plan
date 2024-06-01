#include <iostream>
#include <string>
#include <list>
#include <memory>
#include "IDGenerator.h"
#ifndef ORDER_H
#define ORDER_H
using namespace std;

class Restaurant;

enum class OrderStatus {Received, Preparing, Ready, Completed, Cancelled, Delivered};

struct Item{
    string name;
    double price;
    int amount;
    int id;
    bool operator==(const Item& other) const {
        return (name == other.name) && (price == other.price);
    }

};


struct MenuItem{
    string name;
    double price;
    int id;

    MenuItem(const std::string& name, double price, int id = 1): name(name), price(price), id(id) {}
};

class Order
{
    private: 
        int restaurantId;
        list<Item> items;
        bool isDelivery;
        OrderStatus status;
        int orderId;
        double price;
        bool isCancelled;

    public:
        Order();
        Order(int restaurantId, const list<Item>& items, bool isDelivery);
        int get_res_id() const;
        int get_id() const;
        list<Item>& get_items();
        bool is_delivery(){
            return isDelivery;
        }
        const list<Item> get_items() const;
        void add_item(const string& item_name, list<MenuItem>& menu);
        //void remove_item(const string& item_name);
        double get_total() const;
        void change_status();
        void cancelled();
        void set_total_price(double newprice);
        OrderStatus get_status() const;
        void get_item_list() const;
        void display_order() const;
        shared_ptr<Order> clone() const {
            return make_shared<Order>(*this);
        }
};
const MenuItem& find_item_on_menu(const list<MenuItem>& menu, const string& name);
list<Item>::iterator is_item_in_order(list<Item>& items, const string& name);


#endif