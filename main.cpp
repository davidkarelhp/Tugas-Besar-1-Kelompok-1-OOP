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
#include "Player/Player.hpp"

using namespace std;


int main() {
  string configPath = "./config";
  Player mobita(configPath);
  mobita.play();
  return 0;
}
