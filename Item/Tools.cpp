#include "Tools.hpp"

Tools::Tools(int id, string name, string type, int quantity) : Item(id, name, type, quantity) {
    this->durability = 10;
}

int Tools::getDurability() const {
    return this->durability;
}

void Tools::useTool() {
    this->durability -= 1;
    // kalau 0 toolnya dihapus
}