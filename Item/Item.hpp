#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <iostream>
#include <bits/stdc++.h>
#include "Triplet.hpp"

using namespace std;

class Item {
    protected:
        static unordered_map<string, Triplet<int, string, bool>> itemMap;

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

        void setQuantity(int val);

        static void setMap(string key, Triplet<int, string, bool> value) {
            Item::itemMap[key] = value;
        }
        static Triplet<int, string, bool> getMap(string key) {
            return Item::itemMap[key];
        }
        static Item * createItem(string name, int quantity);

        static bool keyExists(string);

        virtual bool isTool() =  0;
};

#endif