#include "Triplet.hpp"
#include <iostream>

Triplet::Triplet() {
    
}

Triplet::Triplet(int id, std::string typeItem, bool tool) {
    this->id = id;
    this->typeItem = typeItem;
    this->tool = tool;
}

int Triplet::getId() {
    return this->id;
}

std::string Triplet::getTypeItem() {
    return this->typeItem;
}

bool Triplet::isTool() {
    return this->tool;
}