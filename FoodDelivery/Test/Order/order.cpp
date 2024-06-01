#include <iostream>
#include "order.h"
#include "IDGenerator.h"
#include <algorithm>
#include "restaurant_getter.h"

using namespace std;

Order::Order(int restaurantId, const list<Item>& items, bool isDelivery): restaurantId(restaurantId), items(items), isDelivery(isDelivery), status(OrderStatus::Received), 
orderId(IDGenerator::generateId("Order")){
    price = 0.0;
    isCancelled = 0;
    
}

int Order::get_res_id() const{
    return restaurantId;
}

int Order::get_id() const{
    return orderId;
}

void Order::cancelled(){
    status = OrderStatus::Cancelled;
}

OrderStatus Order::get_status() const{
    return status;
}

const list<Item> Order::get_items() const{
    return items;
}

double Order::get_total() const{
    return price;
}

void Order::set_total_price(double newprice) {
    price = newprice;
}

list<Item>& Order::get_items(){
    return items;
}

const MenuItem& find_item_on_menu(const list<MenuItem>& menu, const string& name) {
    // for (const auto& item : menu) {
    //     if (item.name == name) {
    //         return item;
    //     }
    // }
    // // If the item with the given name is not found, throw an exception or handle it appropriately
    // throw std::runtime_error("Item with name " + name + " not found on menu.");
    auto it = find_if(menu.begin(), menu.end(), [&name](const MenuItem& item){
        return item.name == name;
    });
    if(it!=menu.end())
        return *it;
    throw runtime_error("Error: Item with name " + name + " not found in menu.");
}

void Order::change_status(){
    if(status == OrderStatus::Completed && isDelivery){
        get_restaurant(get_res_id()).remove_delivery_by_ordId(get_id());
        status = OrderStatus::Delivered;
            
    }
        switch (status)
        {
        case (OrderStatus::Received):
            status = OrderStatus::Preparing;
            break;
        case (OrderStatus::Preparing):
            status = OrderStatus::Ready;
            break;
        case (OrderStatus::Ready):
            status = OrderStatus::Completed;
            break;
        default:
            cout << "This order has been completed";
        }

}

void Order::add_item(const string& item_name, list<MenuItem>& menu){
    try{
        auto item = is_item_in_order(items, item_name);
        item->amount +=1;
    }
    catch(const runtime_error&){
        auto item = find_item_on_menu(menu, item_name);
        items.push_back({item_name, item.price, 1, item.id});
    }
}
//find the item and if it exists add to number


list<Item>::iterator is_item_in_order(std::list<Item>& items, const std::string& name) {
    // for (auto it = items.begin(); it != items.end(); ++it) {
    //     if (it->name == name) {
    //         return it;
    //     }
    // }
    auto it = find_if(items.begin(), items.end(), [&name](Item& item){
        return name == item.name;
    });
    if(it != items.end())
        return it;

    throw std::runtime_error("Item with name " + name + " not found.");
}

void Order::get_item_list() const{
    list<Item>:: iterator const it;
    for (  auto it = items.begin(); it != items.end(); ++it)
        cout << "Name: " << it->name << "\tPrice: " << it->price <<"\tAmount: "<< it->amount<<'\n';
}

void Order::display_order() const {
    cout << "Order ID: " << orderId << endl;
    cout << "Items:" << endl;
    for (const auto& item : items) {
        cout << "- " << item.name << ' ' << item.price << ", amount: " << item.amount<< endl;
    }
    cout << "Total Price: $" << price << endl;
    cout << "Status: ";
    switch (status) {
        case OrderStatus::Received:
            cout << "Received";
            break;
        case OrderStatus::Preparing:
            cout << "Preparing";
            break;
        case OrderStatus::Ready:
            cout << "Ready";
            break;
        case OrderStatus::Completed:
            cout << "Completed";
            break;
        case OrderStatus::Cancelled:
            cout << "Cancelled";
            break;
        case OrderStatus::Delivered:
            cout << "Delivered";
            break;
    }
    cout << endl;
}

