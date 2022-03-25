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

  cout << R"(
███╗░░░███╗░█████╗░██╗███╗░░██╗██╗░░██╗██████╗░███████╗███████╗████████╗
████╗░████║██╔══██╗██║████╗░██║██║░██╔╝██╔══██╗██╔════╝██╔════╝╚══██╔══╝
██╔████╔██║███████║██║██╔██╗██║█████═╝░██████╔╝█████╗░░█████╗░░░░░██║░░░
██║╚██╔╝██║██╔══██║██║██║╚████║██╔═██╗░██╔══██╗██╔══╝░░██╔══╝░░░░░██║░░░
██║░╚═╝░██║██║░░██║██║██║░╚███║██║░╚██╗██║░░██║███████╗██║░░░░░░░░██║░░░
╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝╚═╝░░░░░░░░╚═╝░░░)" << endl;

  cout << endl;
  cout << "Brought to you by: BaikBaik Saja" << endl;
  cout << endl;

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

  return 0;
}
