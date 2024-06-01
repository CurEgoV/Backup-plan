#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "customer.h"
#include "delivery.h"
#include <memory>

#ifndef RESTAURANT_H
#define RESTAURANT_H

using namespace std;

//the list of customers may be a list of structs with customer ptr
//and description if the customer is active //to be considered

extern std::list<Restaurant> restaurants;

class Restaurant
{
private:
    string name;
    void make_menu(const list<MenuItem>& menu) {
    int menu_item_id = 1;
    for (auto& item : menu) {
         MenuItem menuItem = item;
        menuItem.id = menu_item_id++;
        this->menu.push_back(menuItem);
        }
    }
    list<MenuItem> menu;
    int restaurantId;
    list<unique_ptr<Delivery>> deliveries;
    list<shared_ptr<Customer>> customers;
    list<shared_ptr<Order>> orders;
public:
    Restaurant(const string& name, const list<MenuItem>& menu);
    ~Restaurant();
    void update_status(int orderId);
    void set_name(const string& newName);
    const string& get_name();
    void add_order(std::shared_ptr<Order> order);
    void add_to_menu(const MenuItem& item);
    int get_id() const;
    // Delete copy constructor and = op, (cuz of deliveries to avoid copy risk)
    Restaurant(const Restaurant&) = delete;
    Restaurant& operator=(const Restaurant&) = delete;
    //making restaurant kind of a like a unique ptr because of deliveries being unique pointers
    Restaurant(Restaurant&&) = default;
    Restaurant& operator=(Restaurant&&) = default;

    bool make_delivery(int cusId, int ordId);//only used if the order isn't for pickup
    void display_menu();
    void take_order(list <Item> orderItems, int customerId, bool isDelivery);
    void order_list();
    const list<shared_ptr<Customer>>& get_customer_list() const;
    const list<unique_ptr<Delivery>>& get_delivery_list() const;
    void remove_delivery_by_ordId(int orderId);
    const list <MenuItem>& get_menu() const;
    void add_customer(Customer& customer);
    list <MenuItem>& get_menu(){
        return menu;
    }
    const Delivery& get_delivery_delId(int delId);
    const Delivery& get_delivery_ordId(int ordId);
    void change_order_status(int ordId);
    Order& get_order(int ordId);
    Customer& find_customer(int customerId);
};
void are_items_in_menu(const list<MenuItem>& menu, const list<string>& orderItems, list<Item>& validItems, list<string>& invalidItems, double& total);



#endif