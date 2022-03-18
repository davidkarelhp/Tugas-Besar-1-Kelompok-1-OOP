#ifndef __RECIPE_TRIE_HPP__
#define __RECIPE_TRIE_HPP__

#include <iostream>
#include <bits/stdc++.h>

using namespace std;


class TrieNode {
    private:
        unordered_map<string, TrieNode*> node;

    public:
        void set(string key, TrieNode * value) {
            this->node[key] = value;
        }

        TrieNode * get(string key) {
            return this->node[key];
        }
};

class RecipeTrie {
    private:
        TrieNode * root;

        TrieNode * getLastNode(string* recipeArr, int n) {
            TrieNode * currentNode;

            currentNode = this->root;
            for (int i = 0; i < n; i++) {
                if (currentNode->get(recipeArr[i]) == nullptr) {
                    return nullptr;
                }
                currentNode = currentNode->get(recipeArr[i]);
            }
            return currentNode;
        }

    public:
        RecipeTrie() {
            this->root = new TrieNode();
        }

        void buildRecipe(int row, int col, string* recipeArr, string result, int quantity) {
            TrieNode * currentNode;
            int recipeLength = row * col, i;

            // currentNode = this->root;
            // for (i = 0; i < recipeLength; i++) {
            //     if (currentNode->get(recipeArr[i]) == nullptr) {
            //         currentNode->set(recipeArr[i], new TrieNode());
            //     }
            //     currentNode = currentNode->get(recipeArr[i]);
            // }
            
            currentNode = this->root;
            int currentIdx = 0;
            for (i = 0; i < row; i++) {
                for (int j = 0; j < 3; j++) {
                    if (j < col) {
                        if (currentNode->get(recipeArr[currentIdx]) == nullptr) {
                            currentNode->set(recipeArr[currentIdx], new TrieNode());
                        }
                        currentNode = currentNode->get(recipeArr[currentIdx]);
                        currentIdx++;
                    } else if (i != row - 1) {
                        if (currentNode->get("-") == nullptr) {
                            currentNode->set("-", new TrieNode());
                        }
                        currentNode = currentNode->get("-");
                    }
                }
            }

            pair<string, int> * resultPair = new pair<string, int>();

            resultPair->first = result;
            resultPair->second = quantity;

            currentNode->set("*", (TrieNode*)resultPair);
        }


        pair<string, int> * checkRecipe(string* recipeArr, int n) {
            TrieNode * temp = this->getLastNode(recipeArr, n);
            if (temp != nullptr && temp->get("*") != nullptr) {
                return (pair<string, int> *)temp->get("*");
            } else {
                return nullptr;
            }
        }
};

#endif