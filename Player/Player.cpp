#include "Player.hpp"
#include "../IO/inputItem/InputItem.hpp"
#include "../IO/inputRecipe/InputRecipe.hpp"
#include "../IO/outputFile/OutputFile.hpp"
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
        try {
            if (command == "EXPORT")
            {
                string outputPath;
                cin >> outputPath;
                OutputFile::outputFile(outputPath);
                cout << "Exported" << endl;
            }
            else if (command == "CRAFT")
            {
                // cout << "TODO" << endl;
                Crafting::craft();
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
        } catch (exception& err) {
            cout << err.what() << endl;
        } catch (BaseException * err) {
            cout << err->message() << endl;
        }
        cout << "Masukkan command: ";
    }
}
