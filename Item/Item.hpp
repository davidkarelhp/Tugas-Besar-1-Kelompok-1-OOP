#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <iostream>
#include <bits/stdc++.h>
#include "Triplet.hpp"

using namespace std;

class Item {
    protected:
        static unordered_map<string, Triplet> itemMap;

        // Atribut objek/instans
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
        static void setMap(string key, Triplet value) {
            Item::itemMap[key] = value;
        }
        static Triplet getMap(string key) {
            return Item::itemMap[key];
        }

        void setQuantity(int val);

        Item * createItem(string name, int quantity);

        virtual bool isTool() =  0;
};

#endif