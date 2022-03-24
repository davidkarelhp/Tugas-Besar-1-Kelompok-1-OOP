#include "Tool.hpp"

Tool::Tool(int id, string name, string type, int quantity) : Item(id, name, type, quantity) {
    this->durability = 10;
}

// Getter
int Tool::getDurability() const {
    return this->durability;
}

// Setter
void Tool::setDurability(int durability) {
    this->durability = durability;
}

void Tool::useTool() {
    this->durability -= 1;
    // kalau 0 toolnya dihapus
}

bool Tool::isTool() {
    return true;
}