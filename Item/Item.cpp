#include "Item.hpp"
#include <bits/stdc++.h>
// #include "Tools.hpp"

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