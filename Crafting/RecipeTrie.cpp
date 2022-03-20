#include "RecipeTrie.hpp"


RecipeTrie::RecipeTrie() {
    this->root = new TrieNode();
}

TrieNode * RecipeTrie::getLastNode(string* recipeArr, int n) {
    TrieNode * currentNode;
    currentNode = this->root;
    // cout << "n: " << n << '\n';
    for (int i = 0; i < n; i++) {
        cout << recipeArr[i] << '\n';
        if (currentNode->get(recipeArr[i]) == nullptr) {
            return nullptr;
        }
        currentNode = currentNode->get(recipeArr[i]);
    }

    return currentNode;
}

void RecipeTrie::buildRecipe(int row, int col, string* recipeArr, string result, int quantity) {
    TrieNode * currentNode;
    int i;
    bool found = false;

    
    currentNode = this->root;
    int currentIdx = 0;
    for (i = 0; i < row; i++) {
        for (int j = 0; j < 3; j++) {
            if (j < col) {
                if (!(recipeArr[currentIdx] == "-" && !found)) {
                    if (currentNode->get(recipeArr[currentIdx]) == nullptr) {
                        currentNode->set(recipeArr[currentIdx], new TrieNode());
                    }
                    currentNode = currentNode->get(recipeArr[currentIdx]);
                }

                if (!found && recipeArr[currentIdx] != "-") {
                    found = true;
                }
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


pair<string, int> * RecipeTrie::checkRecipe(string* recipeArr, int n) {
    TrieNode * temp = this->getLastNode(recipeArr, n);
    if (temp != nullptr && temp->get("*") != nullptr) {
        return (pair<string, int> *)temp->get("*");
    } else {
        return nullptr;
    }
}