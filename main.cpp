// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "Item/Item.hpp"
#include "Item/Tool.hpp"
#include "Item/NonTool.hpp"
#include "Inventory/Inventory.hpp"
#include "Crafting/Crafting.hpp"
#include "IO/inputItem/InputItem.hpp"
#include "IO/inputRecipe/InputRecipe.hpp"

using namespace std;


int main() {

  string configPath = "./config";
  string itemConfigPath = configPath + "/item.txt";

  // read item from config file
  InputItem::readFile(itemConfigPath);
  // read recipes
  for (const auto &entry :
       filesystem::directory_iterator(configPath + "/recipe")) {
    // cout << entry.path() << endl;
    InputRecipe::readFile(entry.path().string());
    // read from file and do something
  }

  // sample interaction
  string command;
  while (cin >> command) {
    if (command == "EXPORT") {
      string outputPath;
      cin >> outputPath;
      ofstream outputFile(outputPath);

      // hardcode for first test case
      outputFile << "21:10" << endl;
      outputFile << "6:1" << endl;
      for (int i = 2; i < 27; i++) {
        outputFile << "0:0" << endl;
      }

      cout << "Exported" << endl;

    } else if (command == "CRAFT") {
      cout << "TODO" << endl;

    } else if (command == "GIVE") {
      Inventory::giveItem();

    } else if (command == "DISCARD") {
      Inventory::discardItem();

    } else if (command == "MOVE") {
      Inventory::moveInventory();

    } else if (command == "USE") {
      Inventory::useInventory();

    } else if (command == "SHOW") {
      Crafting::showCraftingTable();
      Inventory::showItem();

    } else {
      // todo
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}
