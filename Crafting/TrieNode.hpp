#ifndef __TRIE_NODE_HPP__
#define __TRIE_NODE_HPP__

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class TrieNode {
    private:
        unordered_map<string, TrieNode*> node;

    public:
        void set(string, TrieNode *);
        TrieNode * get(string);
};

#endif