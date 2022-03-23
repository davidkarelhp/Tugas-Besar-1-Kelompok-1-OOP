#ifndef __RECIPE_TRIE_HPP__
#define __RECIPE_TRIE_HPP__

#include <iostream>
#include <bits/stdc++.h>
#include "TrieNode.hpp"
#include "../Item/Item.hpp"
#include "../Item/Triplet.hpp"

using namespace std;

class RecipeTrie {
    private:
        TrieNode * root;

        TrieNode * getLastNode(string*, int);

    public:
        RecipeTrie();

        void buildRecipe(int, int, string*, string, int);


        Triplet<string, int, int> * checkRecipe(string*, int, int);
};

#endif