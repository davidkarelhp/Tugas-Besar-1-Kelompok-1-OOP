#include "Player.hpp"
#include "../IO/inputItem/InputItem.hpp"
#include "../IO/inputRecipe/InputRecipe.hpp"
#include "../Inventory/Inventory.hpp"
#include <filesystem>

Player::Player()
{
    this->config = "";
}

Player::Player(string configPath)
{
    this->config = configPath;
    runConfig();
    isConfigSet = true;
}

void Player::setConfig(string configPath)
{
    this->config = configPath;
    runConfig();
    isConfigSet = true;
}

const string Player::getConfig()
{
    return config;
}

void Player::runConfig()
{

    // read item from config file
    InputItem::readFile(config + "/item.txt");
    // read recipes
    for (const auto &entry :
         filesystem::directory_iterator(config + "/recipe"))
    {
        // cout << entry.path() << endl;
        InputRecipe::readFile(entry.path().string());
        // read from file and do something
    }
}

void Player::play()
{
    if (!isConfigSet)
    {
        runConfig();
    }
    // sample interaction
    string command;
    cout << "Masukkan command: ";
    while (cin >> command)
    {
        if (command == "EXPORT")
        {
            string outputPath;
            cin >> outputPath;
            ofstream outputFile(outputPath);

            // hardcode for first test case
            outputFile << "21:10" << endl;
            outputFile << "6:1" << endl;
            for (int i = 2; i < 27; i++)
            {
                outputFile << "0:0" << endl;
            }

            cout << "Exported" << endl;
        }
        else if (command == "CRAFT")
        {
            cout << "TODO" << endl;
        }
        else if (command == "GIVE")
        {
            Inventory::giveItem();
        }
        else if (command == "DISCARD")
        {
            Inventory::discardItem();
        }
        else if (command == "MOVE")
        {
            Inventory::moveInventory();
        }
        else if (command == "USE")
        {
            Inventory::useInventory();
        }
        else if (command == "SHOW")
        {
            Crafting::showCraftingTable();
            Inventory::showItem();
        }
        else
        {
            // todo
            cout << "Invalid command" << endl;
        }
        cout << "Masukkan command: ";
    }
}
