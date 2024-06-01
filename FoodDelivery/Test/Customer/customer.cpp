#include "customer.h"
#include "restaurant.h"
#include "restaurant_getter.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "IDGenerator.h"



Customer::Customer(string name, string phoneNumber, string address):name(name), customerId(IDGenerator::generateId("Customer")){
    contactInf.phoneNumber = phoneNumber;
    contactInf.address = address;
}

int Customer::get_id() const{
    return customerId;
}

const string& Customer::get_name() const{
    return name;
}

void Customer::start_order(const std::list<std::string>& orderItems, int resId, bool isDelivery) {
    try {
        Restaurant& res = get_restaurant(resId);
        list<Item> validItems;
        list<std::string> invalidItems;
        double total =0.0;
        are_items_in_menu(res.get_menu(), orderItems, validItems, invalidItems, total);
        if (!validItems.empty()) {
            auto order = std::make_shared<Order>(resId, validItems, isDelivery);
            order->set_total_price(total);
            res.add_order(order);
            this->add_order(order);
            res.add_customer(*this);

            // add order to the restaurant since its a shared ptr
            
        } else {
            cout << "Invalid order, no items exist." << std::endl;
        }
    } catch (const invalid_argument& error) {
        cout << error.what() << std::endl;
    }
}

// list starts out empty, finds restaurant, the list REMAINS, tho items CAN be there; the items are
// added separately using add_item_to_order.
//  Items can still be added afterwards, until the status of order is Completed

void Customer::cancel_ord(int ordId){
    auto it = orders.begin();
    while(it != orders.end()){
        shared_ptr<Order> order = *it;
        if (order->get_id() == ordId) {
            if(order->get_status() == OrderStatus::Completed){
                cout << "Cannot cancel the order. It has been completed."<<endl;
                return;
            }
            else{
                (*it)->cancelled();
                orders.erase(it);  
                cout << "Your order has been cancelled." << endl;
            }
            return;
        }
        ++it;
    }
    cout << "Order with ID " << ordId << " not found." << endl;
}

void Customer::change_cnt_inf(const string& newNumber, const string& newAddress){
    contactInf.phoneNumber = newNumber;
    contactInf.address = newAddress;
}

void Customer::add_item_to_order(int ordId, const string& item_name){
    try{
        Order& thisOrder = get_order(ordId);
        Restaurant& res = get_restaurant(thisOrder.get_res_id());
        thisOrder.add_item(item_name, res.get_menu());
    }
    catch(const runtime_error& error){
        cout << error.what() << endl;
    }
    catch(const invalid_argument& error){
        cout << error.what() << endl;
    }
}
//checks if item exists, then adds it the order

void Customer::remove_item_from_order(int ordId, const std::string& item_name) {
    try {
        Order& thisOrder = get_order(ordId);
        list<Item>& items = thisOrder.get_items(); // Assuming get_items returns a non-const reference
        auto itemIt = is_item_in_order(items, item_name);
        items.erase(itemIt);
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

Order& Customer::get_order(int ordId) {
    // for(auto const& i: orders){
    //     if(i->get_id()==ordId)
    //         return *i;
    // }
    auto it = find_if(orders.begin(), orders.end(), [ordId](shared_ptr<Order>& order){
        return ordId==order->get_id();
        });
    if(it != orders.end()){
        return **it;
    }
    throw invalid_argument("Order with given ID not found");
}


//maybe make a function to print one order and then use it to print the list of orders
void Customer::pick_up_order(int ordId){
    Order& thisOrder = get_order(ordId);
    thisOrder.change_status();
}

void Customer::add_order(shared_ptr<Order> order){
    orders.push_back(order);
}