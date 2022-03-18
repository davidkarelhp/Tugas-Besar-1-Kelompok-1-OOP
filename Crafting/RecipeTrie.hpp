#ifndef __RECIPE_TRIE_HPP__
#define __RECIPE_TRIE_HPP__

#include <iostream>
#include <bits/stdc++.h>
#include "TrieNode.hpp"

using namespace std;

class RecipeTrie {
    private:
        TrieNode * root;

        TrieNode * getLastNode(string*, int);

    public:
        RecipeTrie() {
            this->root = new TrieNode();
        }

        void buildRecipe(int, int, string*, string, int);


        pair<string, int> * checkRecipe(string*, int);
};

#endif