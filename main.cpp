// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>
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
  //cout << setw(25);
  //cout << "hello  world" << endl;
  cout << R"(
███╗░░░███╗░█████╗░██╗███╗░░██╗██╗░░██╗██████╗░███████╗███████╗████████╗
████╗░████║██╔══██╗██║████╗░██║██║░██╔╝██╔══██╗██╔════╝██╔════╝╚══██╔══╝
██╔████╔██║███████║██║██╔██╗██║█████═╝░██████╔╝█████╗░░█████╗░░░░░██║░░░
██║╚██╔╝██║██╔══██║██║██║╚████║██╔═██╗░██╔══██╗██╔══╝░░██╔══╝░░░░░██║░░░
██║░╚═╝░██║██║░░██║██║██║░╚███║██║░╚██╗██║░░██║███████╗██║░░░░░░░░██║░░░
╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝╚═╝░░░░░░░░╚═╝░░░)" << endl;

  //cout << setw(30);
  cout << endl;
  cout << "Brought to you by: BaikBaik Saja" << endl;
  cout << endl;
  // cout << setw(25);
  // cout << "Commands:" << endl;
  // cout << ">>> GIVE <ITEM_NAME> <ITEM_QTY>" << endl;
  // cout << ">>> DISCARD <INVENTORY_SLOT_ID> <ITEM_QTY>" << endl;
  // cout << ">>> MOVE <INVENTORY_SLOT_ID> N <CRAFTING_SLOT_ID_1>" << endl;
  // cout << ">>> MOVE <INVENTORY_SLOT_ID_SRC> 1 <INVENTORY_SLOT_ID_DEST>" << endl;
  // cout << ">>> MOVE <CRAFTING_SLOT_ID> 1 <INVENTORY_SLOT_ID>" << endl;


  // cout << ">>> USE <INVENTORY_SLOT_ID>" << endl;
  // cout << ">>> CRAFT" << endl;
  // cout << "EXPORT <NAMA_FILE>" << endl;
  // cout << endl;
  // cout << setw(0);
  cout << R"(
     _______________________________________________________________
    /\                                                              \
    \_| Commands:                                                   |
      | >>> GIVE <ITEM_NAME> <ITEM_QTY>                             |
      | >>> DISCARD <INVENTORY_SLOT_ID> <ITEM_QTY>                  |
      | >>> MOVE <INVENTORY_SLOT_ID> N <CRAFTING_SLOT_ID_1>"        |
      | >>> MOVE <INVENTORY_SLOT_ID_SRC> 1 <INVENTORY_SLOT_ID_DEST> |
      | >>> MOVE <CRAFTING_SLOT_ID> 1 <INVENTORY_SLOT_ID>           |
      | >>> USE <INVENTORY_SLOT_ID>                                 |
      | >>> CRAFT                                                   |
      | >>> EXPORT <NAMA_FILE>                                      |
      |   __________________________________________________________|_
       \_/____________________________________________________________/
  )";
  cout << endl << endl << endl;
  mobita.play();
  //cout << "hello world" << endl;
  return 0;
}
