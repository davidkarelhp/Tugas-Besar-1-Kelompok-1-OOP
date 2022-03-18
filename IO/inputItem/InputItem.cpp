#include "InputItem.hpp"
#include <bits/stdc++.h>


void InputItem::readLine(string line) {
    stringstream ss(line);
    int i = 0;
    string name, typeItem, word;
    bool tool;
    int id;

    while (i < 4) {
        ss >> word;
        if (i == 0) {
            id = stoi(word);
        } else if (i == 1) {
            name = word;
        } else if (i == 2) {
            typeItem = word;
        } else {
            tool = word == "TOOL";
        }
        i++;
    }
    Triplet triplet(id, typeItem, tool);
    Item::setMap(name, triplet);
}