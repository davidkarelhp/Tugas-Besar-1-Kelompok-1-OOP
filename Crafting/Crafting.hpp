#ifndef __CRAFTING_HPP__
#define __CRAFTING_HPP__

#include "RecipeTrie.hpp"
#include "../Item/Item.hpp"

class Crafting {
    public:
        static RecipeTrie trie;
        static Item * craftingTable[3][3];
        static void showCraftingTable();
        static void setCraftingSlot(int, Item *, bool);
        static Item * getCraftingSlot(int);

};

#endif