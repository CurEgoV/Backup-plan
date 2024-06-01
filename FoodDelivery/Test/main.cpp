#include <iostream>
#include <list>
#include "restaurant.h"
#include "customer.h"
#include "order.h"
#include "restaurant_getter.h"
#include "IDGenerator.h"
using namespace std;

// Utility function to print test results
void print_test_result(const std::string& test_name, bool result) {
    std::cout << (result ? "[PASS] " : "[FAIL] ") << test_name << std::endl;
}

// Test Restaurant class
void test_restaurant() {
    list<MenuItem> menu = {{"Burger", 5.99}, {"Pizza", 8.99}, {"Salad", 4.99}};
    Restaurant res("Testaurant", menu);
    
    print_test_result("Restaurant Name", get_restaurant(1).get_name() == "Testaurant");
    print_test_result("Restaurant Menu Size", get_restaurant(1).get_menu().size() == 3);
}

// Test Customer class
void test_customer() {
    Customer cus("John Doe", "123456789", "24 Walk Street");
    print_test_result("Customer Name", cus.get_name() == "John Doe");

    list<string> orderItems = {"Burger", "Pizza"};
    Restaurant& res = get_restaurant("Testaurant");
    cus.start_order(orderItems, res.get_id(), true);
    
    print_test_result("Customer Order List Size", cus.get_order_list().size() == 1);

    auto orders = cus.get_order_list();
    if (!orders.empty()) {
        shared_ptr<Order> order = orders.front();
        print_test_result("Order Restaurant ID", order->get_res_id() == res.get_id());
        print_test_result("Order Items Size", order->get_items().size() == 2);
        print_test_result("Order Status", order->get_status() == OrderStatus::Received);
    }
}

// Test Order class
void test_order() {
    Customer cus("Kyle Mack", "123456789", "24 Walk Street");
    list<string> orderItems = {"Burger", "Pizza"};
    cus.start_order(orderItems, 1, true);
  
    //Retrieve the list of orders for the customer
    auto orders = cus.get_order_list();
    //Ensure there is at least one order and get the first order's ID
    print_test_result("Customer Order List Size", orders.size() == 1);
    if (!orders.empty()) {
        shared_ptr<Order> order = orders.front(); // Get the first order
        print_test_result("Order ID from order list", order->get_id()==2); //2 because order with id 1 was previously generated in another customer

        print_test_result("Order Total Price", order->get_total() == 14.98); 
        order->set_total_price(14.98);
        print_test_result("Order Set Total Price", order->get_total() == 14.98);

        Restaurant& res = get_restaurant(1);
        order->add_item("Salad", res.get_menu());
        print_test_result("Order Items Size After Adding Item", order->get_items().size() == 3);
    }
    
}

// Test Delivery class
void test_delivery() {
    Delivery delivery(1, 1);
    delivery.change_status();
    
    print_test_result("Delivery Status Change", delivery.get_status() == DeliveryStatus::EnRoute);
    delivery.change_status();
    print_test_result("Delivery Status Change to Delivered", delivery.get_status() == DeliveryStatus::Delivered);

    delivery.change_status(); // Should not change status further
    print_test_result("Delivery Status Should Remain Delivered", delivery.get_status() == DeliveryStatus::Delivered);


}

void test_customer_restaurant_delivery_integration(){
    Customer cus("Johnatan Smith", "4444444444", "Free Street");
    list<MenuItem> menu = {{"Burger", 1.99}, {"Nuggets", 4.79}, {"Pizza pepperoni", 8.99}, {"Pizza margharita", 6.99}};
    Restaurant res2("Fun mealz", menu);
    
    list<string> orderItems = {"Burger", "Nuggets"};
    Restaurant& res = get_restaurant("Fun mealz");
    cus.start_order(orderItems, res.get_id(), true);
    for(auto& cus: res.get_customer_list()){
        for(auto& ord : cus->get_order_list()){
            ord->display_order();
        }
    }
    auto orders = cus.get_order_list();
    print_test_result("Customer Order List Size (Integration)", orders.size() == 1);

    if (!orders.empty()) {
        shared_ptr<Order> order = orders.front();
        bool deliveryNotMade = res.make_delivery(order->get_id(), cus.get_id());
        print_test_result("Recognises wrong Delivery", !deliveryNotMade);//false, since order status is Received
        
        res.get_order(3).change_status();//restaurant changes the status, here it is Preparing
        res.get_order(3).change_status();//status is Ready
        bool deliveryMade = res.make_delivery(order->get_id(), cus.get_id());
        print_test_result("Make Delivery", deliveryMade);
        const Delivery& del = res.get_delivery_ordId(order->get_id());
        print_test_result("Delivery Status (integration)", del.get_status()==DeliveryStatus::InPickup);

        if (deliveryMade) {
            const auto& deliveries = res.get_delivery_list();
            print_test_result("Restaurant Delivery List Size", deliveries.size() == 1);
            
            Delivery& delivery = *deliveries.front();
            print_test_result("Delivery Customer ID", delivery.get_customer_id() == 3);
            print_test_result("Delivery Order ID", delivery.get_order_id() == order->get_id());
            
            const_cast<Delivery&>(delivery).change_status(); // InPickup -> EnRoute
            print_test_result("Delivery Status Change to EnRoute (Integration)", delivery.get_status() == DeliveryStatus::EnRoute);
            
            const_cast<Delivery&>(delivery).change_status(); // EnRoute -> Delivered
            print_test_result("Delivery Status Change to Delivered (Integration)", delivery.get_status() == DeliveryStatus::Delivered);
            
            print_test_result("Delivery Delivered Check (Integration)", delivery.delivered() == true);
        }
        
    }
    
}

int main() {
    test_restaurant();
    test_customer();
    test_order();
    test_delivery();
    test_customer_restaurant_delivery_integration();


    
    //Try an actual situation 
    // Create a menu, display it and check if adding works
    {
        Restaurant res1("McDonald's", {});
        get_restaurant("McDonald's").add_to_menu({"Pizza", 2.55});
        //get_restaurant(1).display_menu();
    }
    //testing restaurants same name (last restaurant remains on the global list of restaurants)
    {
        list<MenuItem> menu = {
        {"Burger", 5.99},
        {"Fries", 2.99},
        {"Soda", 1.49}
        };
        Restaurant res("McDonald's", menu);

       // get_restaurant("McDonald's").display_menu();


        Restaurant res2("Flurry", {});
        cout << "Restaurant Flurry ID: "<< get_restaurant("Flurry").get_id()<< endl;

    }
    //testing customer creation, order creation
    {
        Customer cus1("John Doe", "123456789", "24 Walk Street");
        cout <<"Customer id: " << cus1.get_id() << "\tName: " << cus1.get_name() << endl << endl;
        cus1.start_order({"Burger", "Fries"}, 3, 0);
        Customer cus2("Peter", "0443548639", "New York City, White House");
        cus1.start_order({"Pizza"}, 1, 0);
        for(auto& ord : cus1.get_order_list()){
            ord->display_order();
        }
       cus1.add_item_to_order(4,"Pizza");
       cus1.add_item_to_order(4,"Cream");//cannot add, item not found
        cus1.cancel_ord(3);
    }
    return 0;
}

//valgrind is checked, no memory leaks nor errors




