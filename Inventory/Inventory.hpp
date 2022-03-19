#ifndef __INVENTORY_HPP__
#define __INVENTORY_HPP__

#include "../Item/Item.hpp"
#include "../Exception/NotIntegerException.hpp"

using namespace std;

class Inventory {
    private:
        static Item * buffer[3][9];
    public:
        static void showItem();
        static void giveItem();
        static void discardItem();
        static void moveInventory();
        static void useInventory();


        
};

#endif