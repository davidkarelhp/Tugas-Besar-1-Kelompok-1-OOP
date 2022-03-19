#include "Inventory.hpp"
#include "../Exception/NotIntegerException.hpp"

Item * Inventory::buffer[3][9] = {};

void Inventory::showItem() {
    cout << "INVENTORY\n";
    int id, quantity;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 9; j++) {
            if (buffer[i][j] == nullptr) {
                cout << "[-1 00]";
            } else {
                id = Inventory::buffer[i][j]->getId();
                quantity = Inventory::buffer[i][j]->getQuantity();
                if (id < 10) {
                    cout << "[0" << Inventory::buffer[i][j]->getId();
                } else {
                    cout << "[" << Inventory::buffer[i][j]->getId();
                }

                cout << " ";

                if (quantity < 10) {
                    cout << "0" << Inventory::buffer[i][j]->getQuantity() << "]";
                } else {
                    cout << Inventory::buffer[i][j]->getQuantity() << "]";
                }
            }
            
            if (j != 8) {
                cout <<" ";
            }
        }
        cout << '\n';
    }
    cout << '\n';
}