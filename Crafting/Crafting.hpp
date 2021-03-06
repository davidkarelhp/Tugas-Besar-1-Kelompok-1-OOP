#ifndef __CRAFTING_HPP__
#define __CRAFTING_HPP__

#include "RecipeTrie.hpp"
#include "../Item/Item.hpp"

class Crafting {
    private:
        static int startLeftIdx[2];
        static int endLeftIdx[2];
        static int startRightIdx[2];
        static int endRightIdx[2];
        static int filledSlot;
        static int toolsQuantity;
        static int minQuantity;
        static void clear(int);
        static Triplet<string, int, int> * checkCraftingConfiguration();

    public:
        static RecipeTrie trie;
        static Item * craftingTable[3][3];
        static void showCraftingTable();
        static void setCraftingSlot(int, Item *);
        static void deleteCraftingSlot(int);
        static Item * getCraftingSlot(int);
        static void craft();

};

#endif