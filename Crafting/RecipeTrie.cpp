#include "RecipeTrie.hpp"


RecipeTrie::RecipeTrie() {
    this->root = new TrieNode();
}

TrieNode * RecipeTrie::getLastNode(string* recipeArr, int n) {
    TrieNode * currentNode;
    string temp;

    currentNode = this->root;
    for (int i = 0; i < n; i++) {
        if (currentNode->get(recipeArr[i]) == nullptr) {
            temp = Item::getMap(recipeArr[i]).getSecond();
            // cout << "type : " << temp << '\n';
            if (temp == "-") {
                return nullptr;
            } else {
                if (currentNode->get(temp) == nullptr) {
                    return nullptr;
                }
                currentNode = currentNode->get(temp);
            }
        } else {
            currentNode = currentNode->get(recipeArr[i]);
        }
    }

    // return nullptr;
    return currentNode;
}

void RecipeTrie::buildRecipe(int row, int col, string* recipeArr, string result, int quantity) {
    TrieNode * currentNode;
    int i;
    bool found = false;
    Triplet<string, int, int> * resultTriplet = new Triplet<string, int, int>();
    resultTriplet->setFirst(result);
    resultTriplet->setSecond(quantity);
    resultTriplet->setThird(row);
    
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
    currentNode->set("*", (TrieNode*)resultTriplet);
}


Triplet<string, int, int> * RecipeTrie::checkRecipe(string* recipeArr, int n, int rowCount) {
    TrieNode * temp = this->getLastNode(recipeArr, n);
    if (temp != nullptr && temp->get("*") != nullptr && ((Triplet<string, int, int> *)temp->get("*"))->getThird() == rowCount) {
        return (Triplet<string, int, int> *)temp->get("*");
    } else {
        return nullptr;
    }
}