#include "InputItem.hpp"
#include <bits/stdc++.h>

void InputItem::readLine(string line)
{
    stringstream ss(line);
    int i = 0;
    string name, typeItem, word;
    bool tool;
    int id;

    while (i < ItemAttributes::tool + 1)
    {
        ss >> word;
        if (i == ItemAttributes::id)
        {
            id = stoi(word);
        }
        else if (i == ItemAttributes::name)
        {
            name = word;
        }
        else if (i == ItemAttributes::type)
        {
            typeItem = word;
        }
        else
        { // ItemAttributes::tool
            tool = word == "TOOL";
        }
        i++;
    }
    Triplet triplet(id, typeItem, tool);
    Item::setMap(name, triplet);
}

void InputItem::readFile(string path)
{
    ifstream dataStream;
    dataStream.exceptions(ifstream::badbit);
    try
    {
        string item;
        dataStream.open(path);
        while (getline(dataStream, item))
        {
            InputItem::readLine(item);
        }
    }
    catch (const ifstream::failure &e)
    {
        dataStream.close();
        cout << "Gagal membuka file konfigurasi item" << endl;
    }
    dataStream.close();
}