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
        Item(const Item& item);
        ~Item();
    
        int getId() const;
        string getName() const;
        string getType() const;
        int getQuantity() const;

        void setQuantity(int val);
        //virtual int getType() const;
};

class Tools : public Item {
    private:
        int durability;
    public:
        Tools(int id, string name, string type, int quantity);
        
        int getDurability() const;
        void useTool();
        //int getType();
};

#endif