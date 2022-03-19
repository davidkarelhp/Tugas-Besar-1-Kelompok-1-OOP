#include "Crafting.hpp"

RecipeTrie Crafting::trie = RecipeTrie();

Item * Crafting::craftingTable[3][3] = {{nullptr, nullptr, nullptr}, {nullptr, nullptr, nullptr}, {nullptr, nullptr, nullptr}};

void Crafting::showCraftingTable() {
    cout << "CRAFTING TABLE\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (craftingTable[i][j] == nullptr) {
                cout << "[-1 00]";
            } else {
                int id = Crafting::craftingTable[i][j]->getId();
                int quantity = Crafting::craftingTable[i][j]->getQuantity();
                if (id < 10) {
                    cout << "[0" << id;
                } else {
                    cout << "[" << id;
                }

                cout << " ";

                if (quantity < 10) {
                    cout << "0" << quantity << "]";
                } else {
                    cout << quantity << "]";
                }
            }

            if (j != 8) {
                cout <<" ";
            }
        }
        cout << '\n';
    }
    cout << '\n';
}

void Crafting::setCraftingSlot(int slotId, Item * item, bool del) {
    int row = slotId / 3, col = slotId % 3;
    if (Crafting::craftingTable[row][col] != nullptr && del) {
        delete Crafting::craftingTable[row][col];
    }
    
    Crafting::craftingTable[row][col] = item;
}

Item * Crafting::getCraftingSlot(int slotId) {
    int row = slotId / 3, col = slotId % 3;

    return Crafting::craftingTable[row][col];
}