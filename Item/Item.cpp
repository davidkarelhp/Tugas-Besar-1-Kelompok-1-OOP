#include "Item.hpp"
#include <bits/stdc++.h>
#include "Tool.hpp"
#include "NonTool.hpp"

using namespace std;

unordered_map<string, Triplet<int, string, bool>> Item::itemMap = unordered_map<string, Triplet<int, string, bool>>();

Item::Item() {}

Item::Item(int id, string name, string type, int quantity) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->quantity = quantity;
}
Item::Item(const Item& item) {}
Item::~Item() {}
    
int Item::getId() const {
    return this->id;
}
string Item::getName() const {
    return this->name;
}
string Item::getType() const {
    return this->type;
}
int Item::getQuantity() const {
    return this->quantity;
}
        
void Item::setQuantity(int val) {
    this->quantity = val;
}

Item * Item::createItem(string name, int quantity) {
    Triplet<int, string, bool> triplet;
    triplet = Item::getMap(name);
    
    if (triplet.getThird()) {
        return new Tool(triplet.getFirst(), name, triplet.getSecond(), quantity);
    } else {
        return new NonTool(triplet.getFirst(), name, triplet.getSecond(), quantity);
    }
}

bool Item::keyExists(string key) {
    return Item::itemMap.find(key) != Item::itemMap.end();
}