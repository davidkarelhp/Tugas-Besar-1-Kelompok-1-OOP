#include "Crafting.hpp"

RecipeTrie Crafting::trie = RecipeTrie();

Item * Crafting::craftingTable[3][3] = {};

void Crafting::showCraftingTable() {
    cout << "CRAFTING TABLE\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (craftingTable[i][j] == nullptr) {
                cout << "[-1 00]";
            } else {
                cout << "[" << (Crafting::craftingTable[i][j]->getId() < 10 ? (0 << Crafting::craftingTable[i][j]->getId()) : Crafting::craftingTable[i][j]->getId())
                        << " " << (Crafting::craftingTable[i][j]->getQuantity() < 10 ? 0 << Crafting::craftingTable[i][j]->getQuantity() : Crafting::craftingTable[i][j]->getQuantity()) << "]";
            }

            if (j != 8) {
                cout <<" ";
            }
        }
        cout << '\n';
    }
    cout << '\n';
}