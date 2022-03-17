#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <iostream>

using namespace std;

class Item {
    protected:
        int id;
        string name;
        string type;
        int quantity;

    public:
        Item();
        Item(int id, string name, string type, int quantity);
    
        int getId() const;
        string getName() const;
        int getQuantity() const;
        void setQuantity(int);
        virtual int getType() const;
};

class Tools : public Item {
    private:
        int durability;
    public:
        Tools();
        Tools(int durability);
        
        int getDurability() const;
        void setDurability(int);
        int getType();
};

#endif