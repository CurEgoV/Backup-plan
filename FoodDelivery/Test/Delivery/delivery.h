

#include <iostream>
#include <string>

#ifndef DELIVERY_H
#define DELIVERY_H
enum class DeliveryStatus {InPickup, EnRoute, Delivered, Order_Cancelled};
class Delivery
{
    private:
        int deliveryId;
        int customerId;
        int orderId;
        bool orderCancelled;
        DeliveryStatus status;
    public:

        Delivery(int customerId, int orderId);
    //orderCancelled gets initialized to 0 when delivery is constructed
        void change_status();
        int get_customer_id() const;
        int get_order_id() const;
        DeliveryStatus get_status() const;
        bool delivered();
        int get_id() const;
};

#endif 