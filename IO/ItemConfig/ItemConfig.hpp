#ifndef ITEM_CONFIG_HPP
#define ITEM_CONFIG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "../../Item/Item.hpp"
using namespace std;
class ItemConfig
{
private:
	string path;
	Item& parseItem(string );
public:
	ItemConfig();
	ItemConfig(string path);
	Item *getItemList();
};

#endif
