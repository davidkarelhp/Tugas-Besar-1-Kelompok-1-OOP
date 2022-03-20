#include "Inventory.hpp"
#include "../Item/Tool.hpp"
#include "../Item/Item.hpp"
#include "../Crafting/Crafting.hpp"
#include "../Exception/NotIntegerException.hpp"

Item * Inventory::buffer[3][9] = {
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    };

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
                    cout << "[0" << id;
                } else {
                    cout << "[" << id;
                }

                cout << " ";

                if (quantity < 10) {
                    cout << "0" << quantity << "]";
                } else {
                    cout << quantity << "]";
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

    Inventory::giveAlgorithm(itemName, itemQuantity);
}

void Inventory::giveAlgorithm(string itemName, int itemQuantity) {
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

void Inventory::discardItem() {
    string inventorySlotId;
    int quantity;

    cin >> inventorySlotId >> quantity;

    int slotId = stoi(inventorySlotId.substr(1));

    int row = (slotId / 9), col = (slotId % 9);

    if (slotId < 0 || slotId > 26) {
        cout << "\nSlot Id tidak valid.\n\n";
    } else {
        if (Inventory::buffer[row][col] == nullptr) {
            cout << "\nItem pada inventori I" << slotId << " kosong.\n\n";
        } else {
            if (Inventory::buffer[row][col]->getQuantity() < quantity) {
                cout << "\nJumlah item yang dimasukkan melebihi jumlah item pada inventori I" << slotId << ".\n\n";
            } else {
                Inventory::buffer[row][col]->setQuantity(Inventory::buffer[row][col]->getQuantity() - quantity);

                if (Inventory::buffer[row][col]->getQuantity() == 0) {
                    delete Inventory::buffer[row][col];
                    Inventory::buffer[row][col] = nullptr;
                }

                cout << "\nItem pada inventori I" << slotId << " berhasil di-discard.\n\n";
            }
        }
    }
}

void Inventory::moveInventory() {
    string inventorySlotIdSrc, inventorySlotIdTarget;
    int slotQuantity;

    cin >> inventorySlotIdSrc >> slotQuantity >> inventorySlotIdTarget;
    int slotIdSrc = stoi(inventorySlotIdSrc.substr(1));

    if (inventorySlotIdTarget.substr(0, 1) == "I") {
        int slotIdTarget = stoi(inventorySlotIdTarget.substr(1));
        int rowTarget = (slotIdTarget / 9), colTarget = (slotIdTarget % 9);
        if (inventorySlotIdSrc.substr(0, 1) == "I") {
            int rowSrc = (slotIdSrc / 9), colSrc = (slotIdSrc % 9);
            if (Inventory::buffer[rowSrc][colSrc] == nullptr) {
                cout << "\nTidak ada item yang dapat dipindahkan.\n\n";
            } else {
                if (Inventory::buffer[rowTarget][colTarget] == nullptr) {
                    Inventory::buffer[rowTarget][colTarget] = Inventory::buffer[rowSrc][colSrc];
                    Inventory::buffer[rowSrc][colSrc] = nullptr;
                    cout << "Item berhasil dipindahkan dari inventori I" << slotIdSrc << " ke inventori I" << slotIdTarget << ".\n\n";
                } else {
                    if (Inventory::buffer[rowTarget][colTarget]->getId() != Inventory::buffer[rowSrc][colSrc]->getId()) {
                        cout << "Item pada inventori I" << slotIdSrc << " dan I" << slotIdTarget << " tidak sama.\n\n";
                    } else {
                        if (Inventory::buffer[rowTarget][colTarget]->isTool()) {
                            cout << "\nItem bertipe Tool tidak dapat ditumpuk\n\n";
                        } else {
                            int targetQuantity = min(64, Inventory::buffer[rowTarget][colTarget]->getQuantity() + Inventory::buffer[rowSrc][colSrc]->getQuantity());
                            Inventory::buffer[rowTarget][colTarget] = Inventory::buffer[rowSrc][colSrc];
                            Inventory::buffer[rowTarget][colTarget]->setQuantity(targetQuantity);
                            Inventory::buffer[rowSrc][colSrc] = nullptr;
                            cout << "Item berhasil dipindahkan dari inventori I" << slotIdSrc << " ke inventori I" << slotIdTarget << ".\n\n";
                        }
                    }
                }
            }

        } else //inventorySlotIdSrc.substr(0, 1) == "C"
        {
            // int rowSrc = (slotIdSrc / 3), colSrc = (slotIdSrc % 3);
            Item * temp = Crafting::getCraftingSlot(slotIdSrc);
            // cout << temp->getName() << " " << temp->getId() << '\n';
            
            if (temp == nullptr) {
                cout << "\nTidak ada item yang dapat dipindahkan.\n\n";
            } else {
                if (Inventory::buffer[rowTarget][colTarget] == nullptr) {
                    Inventory::buffer[rowTarget][colTarget] = Item::createItem(temp->getName(), 1);
                } else { // Asumsi item sudah bertipe sama
                    Inventory::buffer[rowTarget][colTarget]->setQuantity(Inventory::buffer[rowTarget][colTarget]->getQuantity() + 1);
                    // delete temp;
                }
                // Crafting::setCraftingSlot(slotIdSrc, nullptr, false);
                Crafting::deleteCraftingSlot(slotIdSrc);
                cout << "\nItem berhasil dipindahkan dari C" << slotIdSrc << " ke I" << slotIdTarget << ".\n\n";
            }

        }
    } else {
        string * tempArr= new string[slotQuantity];
        tempArr[0] = inventorySlotIdTarget;

        for (int i = 1; i < slotQuantity; i++) {
            cin >> tempArr[i];
        }
        int slotIdTarget;
        int rowSrc = (slotIdSrc / 9), colSrc = (slotIdSrc % 9);
        if (Inventory::buffer[rowSrc][colSrc] == nullptr) {
            cout << "\nTidak ada item pada inventori I" << slotIdSrc << ".\n\n";
        } else {
            if (Inventory::buffer[rowSrc][colSrc]->getQuantity() < slotQuantity) {
                cout << "\nItem pada inventori I" << slotIdSrc << " tidak mencukupi.\n\n";
            } else {


                for (int i = 0; i < slotQuantity; i++) {
                    slotIdTarget = stoi(tempArr[i].substr(1));
                    if (Crafting::getCraftingSlot(slotIdTarget) == nullptr) {
                        Crafting::setCraftingSlot(slotIdTarget, Item::createItem(Inventory::buffer[rowSrc][colSrc]->getName(), 1), false);
                    } else {
                        Crafting::setCraftingSlot(slotIdTarget, Item::createItem(Inventory::buffer[rowSrc][colSrc]->getName(), 1), true);
                    }
                }

                Inventory::buffer[rowSrc][colSrc]->setQuantity(Inventory::buffer[rowSrc][colSrc]->getQuantity() - slotQuantity);
                if (Inventory::buffer[rowSrc][colSrc]->getQuantity() <= 0) {
                    delete Inventory::buffer[rowSrc][colSrc];
                    Inventory::buffer[rowSrc][colSrc] = nullptr;
                }

                cout << "\nItem berhasil dipindahkan.\n\n";
            }
        }

        delete[] tempArr;
    }
}

void Inventory::useInventory() {
    string inventorySlotId;
    cin >> inventorySlotId;

    int slotId = stoi(inventorySlotId.substr(1));

    int row = slotId / 9, col = slotId % 9;

    if (Inventory::buffer[row][col] == nullptr) {
        cout << "\nTidak ada item pada inventori I"<< slotId <<".\n\n";
    } else {
        if (Inventory::buffer[row][col]->isTool()) {
            ((Tool*)Inventory::buffer[row][col])->useTool();
            cout << "\nTool pada inventori I" << slotId << " digunakan.\n";
            if (((Tool*)Inventory::buffer[row][col])->getDurability() <= 0) {
                cout << "Durability habis, Tool hancur.\n";
                delete Inventory::buffer[row][col];
                Inventory::buffer[row][col] = nullptr;
            }
            cout << '\n';
        } else {
            cout << "\nItem pada inventori I"<< slotId <<" tidak bertipe Tool sehingga tidak dapat digunakan.\n\n";
        }
    }
}