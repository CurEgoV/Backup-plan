#include "restaurant_getter.h"
#include <stdexcept>

Restaurant& get_restaurant(int resId) {
    for (auto& restaurant : restaurants) {
        if (restaurant.get_id() == resId) {
            return restaurant;
        }
    }
    throw std::invalid_argument("Restaurant with given ID not found");
}

Restaurant& get_restaurant(const std::string& res_name) {
    std::vector<std::reference_wrapper<Restaurant>> matchedRestaurants;

    // Search for restaurants with the given name
    for (auto& restaurant : restaurants) {
        if (restaurant.get_name() == res_name) {
            matchedRestaurants.push_back(restaurant);
        }
    }

    // Handle cases based on the number of matches found
    if (matchedRestaurants.size() == 1) {
        return matchedRestaurants.front();
    } else if (matchedRestaurants.size() > 1) {
        std::cout << "Results of search: " << res_name << std::endl;
        for (auto& restaurant : matchedRestaurants) {
            std::cout << restaurant.get().get_name() << "\tID: " << restaurant.get().get_id() << std::endl;
        }

        int id;
        std::cin >> id;

        for (auto& restaurant : matchedRestaurants) {
            if (restaurant.get().get_id() == id) {
                return restaurant;
            }
        }

        throw std::invalid_argument("Invalid restaurant ID");
    }

    throw std::invalid_argument("Restaurant with given name not found");
}

// Restaurant& get_restaurant(string res_name) {
//     list <Restaurant> lst;
//     for (auto& restaurant : restaurants) {
//         if (restaurant.get_name() == res_name) {
//             lst.push_back(restaurant);
//         }
//     }
//     if  (lst.size() == 1){
//         return lst.back();
//     }
//     else if (lst.size() > 1){
//         cout << "Results of search: " << res_name << endl;
//         for (auto& res : lst)
//             cout << res.get_name() << "\tID: " << res.get_id() << endl;
//         int id;
//         cin >> id;
//         for(auto& res : lst){
//             if(res.get_id()==id)
//                 return res;
//         }
//         cout << "Invalid restaurant ID" << endl;
//     }
//     throw std::invalid_argument("Restaurant with given name not found");
// }

// Restaurant& get_restaurant(const std::string& res_name) {
//     Restaurant* foundRestaurant = nullptr;
//     int matchCount = 0;

//     // Search for restaurants with the given name
//     for (auto& restaurant : restaurants) {
//         if (restaurant.get_name() == res_name) {
//             foundRestaurant = &restaurant;
//             matchCount++;
//         }
//     }

//     // Handle cases based on the number of matches found
//     if (matchCount == 1) {
//         return *foundRestaurant;
//     } else if (matchCount > 1) {
//         std::cout << "Results of search: " << res_name << std::endl;
//         for (auto& restaurant : restaurants) {
//             if (restaurant.get_name() == res_name) {
//                 std::cout << restaurant.get_name() << "\tID: " << restaurant.get_id() << std::endl;
//             }
//         }

//         int id;
//         std::cin >> id;

//         for (auto& restaurant : restaurants) {
//             if (restaurant.get_id() == id) {
//                 return restaurant;
//             }
//         }

//         throw std::invalid_argument("Invalid restaurant ID");
//     }

//     throw std::invalid_argument("Restaurant with given name not found");
// }