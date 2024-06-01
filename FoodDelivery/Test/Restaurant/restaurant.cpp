#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include "restaurant.h"
#include "IDGenerator.h"
using namespace std;

list<Restaurant> restaurants;

Restaurant::Restaurant(const string& name, const list<MenuItem>& menu): name(name), restaurantId(IDGenerator::generateId("Restaurant")){
    // for(auto i : menu)
    //     i.id = IDGenerator::generateId("MenuItem");
    make_menu(menu);
    restaurants.push_back(move(*this));
}

Restaurant::~Restaurant() {
    customers.clear();
    orders.clear();
    deliveries.clear();
}

void Restaurant::remove_delivery_by_ordId(int ordId) {
    auto it = find_if(deliveries.begin(), deliveries.end(), [ordId](unique_ptr<Delivery>& delivery){
        return ordId == delivery->get_order_id();
    });
    if(it != deliveries.end()){
        it = deliveries.erase(it);
    }
}
void Restaurant::update_status(int orderId){
    Order& order = get_order(orderId);
    order.change_status();
}
void Restaurant::set_name(const string& newName){
    name = newName;
}
const string& Restaurant::get_name(){
    return name;
}
void Restaurant::add_to_menu(const MenuItem& item) {
    menu.push_back(item);
}
int Restaurant::get_id() const{
    return restaurantId;
}

Customer& Restaurant::find_customer(int customerId){
    // list<shared_ptr<Customer>>::iterator it;
    // for (auto it = customers.begin(); it != customers.end(); ++it){
    //     if((*it)->get_id() == customerId){
    //         return *it->get();
    //     }
    // }
    auto it = find_if(customers.begin(), customers.end(), [customerId](shared_ptr<Customer>& customer){
        return customerId==customer->get_id();
    });
    if(it != customers.end()){
        return **it;
    }
    throw invalid_argument("Customer with given ID not found");
}

void Restaurant::add_customer(Customer& customer){
    for (const auto& cus : customers) {
        if (cus->get_id() == customer.get_id()) {
            std::cerr << "Customer with ID " << cus->get_id() << " already exists." << std::endl;
            return; 
        }
    }
    std::shared_ptr<Customer> newCustomer = std::make_shared<Customer>(customer);
    customers.push_back(newCustomer);
}

void Restaurant::order_list() {
    bool ordersFound = false; // track if any orders were found for the restaurant
    for (auto& customer : customers) {
        for (auto& order : customer->get_order_list()) {
            if (order->get_res_id() == get_id()) {
                cout << "Order ID: " << order->get_id() << "\nItems:" << endl;
                order->get_item_list();
                ordersFound = true; // Set the flag to true if orders are found
            }
        }
    }
    if (!ordersFound) {
        cout << "No orders found for this restaurant." << endl;
    }
}
void Restaurant::take_order(list <Item> orderItems, int customerId, bool isDelivery){
    Customer customer = find_customer(customerId);
    shared_ptr<Order> order = make_shared<Order>(this->get_id(), orderItems, isDelivery);    
    customer.add_order(order);
}


const Delivery& Restaurant::get_delivery_delId(int delId){
    // for (const auto& deliveryPtr : deliveries) {
    //     const Delivery& delivery = *deliveryPtr;
    //     if (delivery.get_id() == delId) {
    //         return delivery;
    //     }
    // }
    auto it = find_if(deliveries.begin(), deliveries.end(), [delId](unique_ptr<Delivery>& delivery){
        return delId==delivery->get_id();
    });
    if(it != deliveries.end())
        return **it;
    throw std::invalid_argument("Delivery with the given order ID not found.");
}
const Delivery& Restaurant::get_delivery_ordId(int ordId){
    // for (const auto& deliveryPtr : deliveries) {
    //     const Delivery& delivery = *deliveryPtr;
    //     if (delivery.get_order_id() == ordId) {
    //         return delivery;
    //     }
    // }
    auto it = find_if(deliveries.begin(), deliveries.end(), [ordId](unique_ptr<Delivery>& delivery){
        return ordId == delivery->get_order_id();
    });
    if (it != deliveries.end())
        return **it;
    throw std::invalid_argument("Delivery with the given order ID not found.");
}

void Restaurant::add_order(shared_ptr<Order> order){
    orders.push_back(order);
}

bool Restaurant::make_delivery(int cusId, int ordId){
    try {
        Order& order = get_order(ordId);
        if(order.get_status() == OrderStatus::Ready && order.is_delivery()==true){
            if(deliveries.size()>3){
                cout << "Order is currently unavailable for delivery";
                return false;
            }
            unique_ptr<Delivery> delivery = std::make_unique<Delivery>(cusId, ordId);
            deliveries.push_back(move(delivery));
            return true;
        }
        return false;
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return false;
}
//only used if the order isn't for pickup


void Restaurant::display_menu(){
    for (const auto& it : menu)
        cout << "ID: " << it.id << "\tName: " << it.name << "\tPrice: " << it.price <<'\n';
}
const list<shared_ptr<Customer>>& Restaurant::get_customer_list() const{
    return customers;
}
const list<unique_ptr<Delivery>>& Restaurant::get_delivery_list() const{
    return deliveries;
}
const list<MenuItem>& Restaurant::get_menu() const{
    return menu;
}
void Restaurant::change_order_status(int ordId){
    Order order = get_order(ordId);
    order.change_status();
}

Order& Restaurant::get_order(int ordId){
    // for(auto const& i : customers){
    //     Customer& customer = *i;
    //     for(auto const& j: customer.get_order_list()){
    //         if (j->get_id()==ordId)
    //             return *j;
    //     }
    // }
    auto it = find_if(orders.begin(), orders.end(), [ordId](shared_ptr<Order>& order){
        return ordId==order->get_id();
    });
    if(it != orders.end())
        return **it;
    throw invalid_argument("Order with given ID not found");
}



void are_items_in_menu(const list<MenuItem>& menu, const list<string>& orderItems, list<Item>& validItems, list<string>& invalidItems, double &total) {
    for (const string& itemName : orderItems) {
        bool itemFound = false;
        for (const auto& menuItem : menu) {
            if (menuItem.name == itemName) {
                validItems.push_back({menuItem.name, menuItem.price, 1, menuItem.id});
                itemFound = true;
                total += menuItem.price;
                break;
            }
        }
        if (!itemFound) {
            invalidItems.push_back(itemName);
        }
    }
    if(!invalidItems.empty()){
        cout<<"Items not found: ";
        for(const auto& itemName : invalidItems)
            cout <<itemName << " ";
        cout << endl;
    }
}
