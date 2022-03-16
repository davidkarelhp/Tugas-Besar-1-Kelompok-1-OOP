#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <iostream>

using namespace std;

class Item {
    protected:
        int id;
        string name;
        int quantity;

    public:
        int getId();
        string getName();
        int getQuantity();
        void setQuantity(int);
        virtual int getType() = 0;
};

#endif