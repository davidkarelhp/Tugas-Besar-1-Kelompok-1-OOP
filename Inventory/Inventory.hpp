#ifndef __INVENTORY_HPP__
#define __INVENTORY_HPP__

#include "../Item/Item.hpp"

using namespace std;

class Inventory {
    private:
        Item * buffer[3][9];
    public:
        void showItem();
        void giveItem();
        
};

#endif