#include "Triplet.hpp"
#include <iostream>

Triplet::Triplet() {
    
}

Triplet::Triplet(int id, std::string typeItem, bool tool) {
    this->id = id;
    this->typeItem = typeItem;
    this->tool = tool;
}