#include "Item.hpp"
#include <bits/stdc++.h>
#include "Tool.hpp"
#include "NonTool.hpp"

using namespace std;

unordered_map<string, Triplet> Item::itemMap = unordered_map<string, Triplet>();

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
    Triplet triplet;
    triplet = Item::getMap(name);
    
    if (triplet.isTool()) {
        return new Tool(triplet.getId(), name, triplet.getTypeItem(), quantity);
    } else {
        return new NonTool(triplet.getId(), name, triplet.getTypeItem(), quantity);
    }
}

bool Item::keyExists(string key) {
    return Item::itemMap.find(key) != Item::itemMap.end();
}