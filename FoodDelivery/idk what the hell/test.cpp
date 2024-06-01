#include <iostream>
#include <vector>

using namespace std;

// Define the ContactInfo struct
struct ContactInfo {
    string phoneNumber;
    string address;
    string email;
    string deliveryInstructions;
};

// Define the Customer class
class Customer {
private:
    static int nextId;
    int customerId;
    string name;

public:
    Customer(string name);
    int get_customer_id() const;
};

// Static member initialization
int Customer::nextId = 1;

// Constructor definition for Customer class
Customer::Customer(string name) : customerId(nextId++), name(name) {}

// Method to get customer ID
int Customer::get_customer_id() const {
    return customerId;
}

// Define the Order class
class Order {
private:
    static int nextOrderId;
    int orderId;

public:
    Order();
    int get_order_id() const;
};

// Static member initialization
int Order::nextOrderId = 1;

// Constructor definition for Order class
Order::Order() : orderId(nextOrderId++) {}

// Method to get order ID
int Order::get_order_id() const {
    return orderId;
}

// Define the Restaurant class
class Restaurant {
private:
    static int nextRestaurantId;
    int restaurantId;

public:
    Restaurant();
    int get_restaurant_id() const;
};

// Static member initialization
int Restaurant::nextRestaurantId = 1;

// Constructor definition for Restaurant class
Restaurant::Restaurant() : restaurantId(nextRestaurantId++) {}

// Method to get restaurant ID
int Restaurant::get_restaurant_id() const {
    return restaurantId;
}

int main() {
    // Create instances of Customer, Order, and Restaurant classes
    Customer customer1("John");
    Customer customer2("Alice");
    Customer customer3("filip");
    Order order1;
    Order order2;
    Restaurant restaurant1;
    Restaurant restaurant2;

    // Print IDs of objects
    cout << "Customer 1 ID: " << customer1.get_customer_id() << endl;
    cout << "Customer 2 ID: " << customer2.get_customer_id() << endl;
     cout << "Customer 3 ID: " << customer3.get_customer_id() << endl;
    cout << "Order 1 ID: " << order1.get_order_id() << endl;
    cout << "Order 2 ID: " << order2.get_order_id() << endl;
    cout << "Restaurant 1 ID: " << restaurant1.get_restaurant_id() << endl;
    cout << "Restaurant 2 ID: " << restaurant2.get_restaurant_id() << endl;

    return 0;
}
