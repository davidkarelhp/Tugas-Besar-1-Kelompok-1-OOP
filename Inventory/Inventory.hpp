#ifndef __INVENTORY_HPP__
#define __INVENTORY_HPP__

#include "../Item/Item.hpp"
#include "../Exception/NotIntegerException.hpp"

using namespace std;

class Inventory {
    private:
        static Item * buffer[3][9];
    public:
        static void showItem();

        static void giveItem() {
            string itemName, itemQuantityString;
            int itemQuantity;
            bool isNumber = true;
            cin >> itemName >> itemQuantityString;
            for (char const &c: itemQuantityString) {
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }

            // Cek Item name valid atau tidak di sini

            // Cek Item adalah non tool di sini

            if (!isNumber) {
                throw new NotIntegerException;
            }

            itemQuantity = stoi(itemQuantityString);

            for (int i = 0; i < 3 && itemQuantity > 0; i++) {
                for (int j = 0; j < 9 && itemQuantity > 0; j++) {
                    if (Inventory::buffer[i][j] != nullptr) {
                        if (Inventory::buffer[i][j]->getName() == itemName && Inventory::buffer[i][j]->getQuantity() < 64) {
                            int itemReduced = min(64 - Inventory::buffer[i][j]->getQuantity(), itemQuantity);
                            itemQuantity -= itemReduced;
                            Inventory::buffer[i][j]->setQuantity(Inventory::buffer[i][j]->getQuantity() + itemReduced);
                        }
                    }
                }
            }

            for (int i = 0; i < 3 && itemQuantity > 0; i++) {
                for (int j = 0; j < 9 && itemQuantity > 0; j++) {
                    if (Inventory::buffer[i][j] == nullptr){
                        int itemReduced = min(64, itemQuantity);
                        itemQuantity -= itemReduced;
                        // Inventory::buffer[i][j]->setQuantity(Inventory::buffer[i][j]->getQuantity() + itemReduced);
                        Inventory::buffer[i][j] = Item::createItem(itemName, itemReduced);
                    }
                }
            }

            if (itemQuantity > 0) {
                cout << "\nItem tidak dimasukkan semua, hanya dimasukkan sebisanya saja.\n\n";
            } else {
                cout << "\nItem berhasil dimasukkan ke inventory.\n\n";
            }
        }
        
};

#endif