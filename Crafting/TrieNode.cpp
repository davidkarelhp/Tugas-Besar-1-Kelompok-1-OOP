#include "TrieNode.hpp"

void TrieNode::set(string key, TrieNode * value) {
    this->node[key] = value;
}

TrieNode * TrieNode::get(string key) {
    return this->node[key];
}