#include "Inventory.hpp"
#include "../Exception/NotIntegerException.hpp"

void Inventory::showItem() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 9; j++) {
            cout << "[" << (this->buffer[i][j]->getId() < 10 ? (0 << this->buffer[i][j]->getId()) : this->buffer[i][j]->getId())
            << " " << (this->buffer[i][j]->getQuantity() < 10 ? 0 << this->buffer[i][j]->getQuantity() : this->buffer[i][j]->getQuantity()) << "]";
            if (j != 8) {
                cout <<" ";
            }
        }
        cout << '\n';
    }
}

void Inventory::giveItem() {
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
            if (this->buffer[i][j]->getName() == itemName && this->buffer[i][j]->getQuantity() < 64) {
                int itemReduced = min(64 - this->buffer[i][j]->getQuantity(), itemQuantity);
                itemQuantity -= itemReduced;
                this->buffer[i][j]->setQuantity(this->buffer[i][j]->getQuantity() + itemReduced);
            }
        }
    }

    for (int i = 0; i < 3 && itemQuantity > 0; i++) {
        for (int j = 0; j < 9 && itemQuantity > 0; j++) {
            if (this->buffer[i][j]->getId() == 0){
                int itemReduced = min(64, itemQuantity);
                itemQuantity -= itemReduced;
                this->buffer[i][j]->setQuantity(this->buffer[i][j]->getQuantity() + itemReduced);
            }
        }
    }

    if (itemQuantity > 0) {
        cout << "\nItem tidak dimasukkan semua, hanya dimasukkan sebisanya saja.\n\n";
    }

}