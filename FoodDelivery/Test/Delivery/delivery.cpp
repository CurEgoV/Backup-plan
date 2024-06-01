#include <iostream>
#include "delivery.h"
#include  "IDGenerator.h"

using namespace std;

    Delivery::Delivery(int customerId, int orderId): deliveryId(IDGenerator::generateId("Delivery")), customerId(customerId), orderId(orderId){
        orderCancelled = false;
        status = DeliveryStatus::InPickup;
    }
    //isCancelled gets initialized to 0 when delivery is constructed
    int Delivery::get_customer_id() const{
        return customerId;
    }
    int Delivery::get_order_id() const{
        return orderId;
    }
    void Delivery::change_status(){
        switch (status)
        {
        case (DeliveryStatus::InPickup):
            status = DeliveryStatus::EnRoute;
            break;
        case (DeliveryStatus::EnRoute):
            status = DeliveryStatus::Delivered;
            break;
        case (DeliveryStatus::Delivered):
            break;
        case (DeliveryStatus::Order_Cancelled):
            break;
        default:
            cout << "This order has been completed";
        }
    }
    DeliveryStatus Delivery::get_status() const{
        return status;
    }
    bool Delivery::delivered(){
        if(get_status() == DeliveryStatus::Delivered)
            return true;
        return false;
    }
    
    int Delivery::get_id() const{
        return deliveryId;
    }