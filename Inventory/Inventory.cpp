#include "Inventory.hpp"
#include "../Item/Tool.hpp"
#include "../Item/Item.hpp"
#include "../Crafting/Crafting.hpp"
#include "../Exception/NotIntegerException.hpp"
#include "../Exception/NotValidItemNameException.hpp"
#include "../Exception/DifferentItemException.hpp"
#include "../Exception/NonStackableToolException.hpp"
#include "../Exception/ItemNotExistException.hpp"
#include "../Exception/NotEnoughItemException.hpp"
#include "../Exception/NonToolUnusableException.hpp"
#include "../Exception/NotValidSlotIdException.hpp"

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
    if (!Item::keyExists(itemName)) {
        throw new NotValidItemNameException;
    }

    if (!isNumber) {
        throw new NotIntegerException;
    }

    itemQuantity = stoi(itemQuantityString);

    Inventory::giveAlgorithm(itemName, itemQuantity, 0);
}

void Inventory::giveAlgorithm(string itemName, int itemQuantity, int durability) {
    Triplet<int, string, bool> triplet;
    int itemReduced, initialQuantity;
    triplet = Item::getMap(itemName);
    initialQuantity = itemQuantity;

    if (!triplet.getThird()) {
        for (int i = 0; i < 3 && itemQuantity > 0; i++) {
            for (int j = 0; j < 9 && itemQuantity > 0; j++) {
                if (Inventory::buffer[i][j] != nullptr) {
                    if (Inventory::buffer[i][j]->getName() == itemName && Inventory::buffer[i][j]->getQuantity() < 64) {
                        itemReduced = min(64 - Inventory::buffer[i][j]->getQuantity(), itemQuantity);
                        itemQuantity -= itemReduced;
                        Inventory::buffer[i][j]->setQuantity(Inventory::buffer[i][j]->getQuantity() + itemReduced);
                    }
                }
            }
        }
    }

    if (itemQuantity > 0) {
        for (int i = 0; i < 3 && itemQuantity > 0; i++) {
            for (int j = 0; j < 9 && itemQuantity > 0; j++) {
                if (Inventory::buffer[i][j] == nullptr){
                    if (!triplet.getThird()) {
                        itemReduced = min(64, itemQuantity);
                    } else {
                        itemReduced = 1;
                    }
                    itemQuantity -= itemReduced;
                    Inventory::buffer[i][j] = Item::createItem(itemName, itemReduced);
                    if (durability != 0) {
                        ((Tool *)Inventory::buffer[i][j])->setDurability(durability);
                    }
                }
            }
        }
    }

    if (itemQuantity == initialQuantity) {
        cout << "\nItem tidak muat dimasukkan ke dalam inventory.\n\n";
    } else if (itemQuantity > 0) {
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

    if (slotId < 0 || slotId > 26) {
        throw new NotValidSlotIdException(true);
    }

    int row = (slotId / 9), col = (slotId % 9);


    if (Inventory::buffer[row][col] == nullptr) {
        throw new ItemNotExistException("I" + to_string(slotId));
    }

    if (Inventory::buffer[row][col]->getQuantity() < quantity) {
        throw new NotEnoughItemException("I" + to_string(slotId));
    }

    Inventory::buffer[row][col]->setQuantity(Inventory::buffer[row][col]->getQuantity() - quantity);

    if (Inventory::buffer[row][col]->getQuantity() == 0) {
        delete Inventory::buffer[row][col];
        Inventory::buffer[row][col] = nullptr;
    }

    cout << "\nItem pada inventori I" << slotId << " berhasil di-discard.\n\n";
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
                throw new ItemNotExistException("I" + to_string(slotIdSrc));
            }

            if (Inventory::buffer[rowTarget][colTarget] == nullptr) {
                Inventory::buffer[rowTarget][colTarget] = Inventory::buffer[rowSrc][colSrc];
                Inventory::buffer[rowSrc][colSrc] = nullptr;
                cout << "Item berhasil dipindahkan dari inventori I" << slotIdSrc << " ke inventori I" << slotIdTarget << ".\n\n";
            } else {
                if (Inventory::buffer[rowTarget][colTarget]->getId() != Inventory::buffer[rowSrc][colSrc]->getId()) {
                    throw new DifferentItemException("I" + to_string(slotIdSrc), "I" + to_string(slotIdTarget));
                }

                if (Inventory::buffer[rowTarget][colTarget]->isTool()) {
                    throw new NonStackableToolException;
                }

                int targetQuantity = min(64, Inventory::buffer[rowTarget][colTarget]->getQuantity() + Inventory::buffer[rowSrc][colSrc]->getQuantity());
                Inventory::buffer[rowTarget][colTarget] = Inventory::buffer[rowSrc][colSrc];
                Inventory::buffer[rowTarget][colTarget]->setQuantity(targetQuantity);
                Inventory::buffer[rowSrc][colSrc] = nullptr;
                cout << "Item berhasil dipindahkan dari inventori I" << slotIdSrc << " ke inventori I" << slotIdTarget << ".\n\n";
            }
        
        } else //inventorySlotIdSrc.substr(0, 1) == "C"
        {
            Item * temp = Crafting::getCraftingSlot(slotIdSrc);
            
            if (temp == nullptr) {
                throw new ItemNotExistException("C" + to_string(slotIdSrc));
            }

            if (Inventory::buffer[rowTarget][colTarget] == nullptr) {
                Inventory::buffer[rowTarget][colTarget] = Item::createItem(temp->getName(), temp->getQuantity());

                if (temp->isTool()) {
                    ((Tool *)Inventory::buffer[rowTarget][colTarget])->setDurability(((Tool *)temp)->getDurability());
                }

                Crafting::deleteCraftingSlot(slotIdSrc);
                cout << "\nItem berhasil dipindahkan dari C" << slotIdSrc << " ke I" << slotIdTarget << ".\n\n";
            } else {
                if (Inventory::buffer[rowTarget][colTarget]->getId() != temp->getId()) {
                    throw new DifferentItemException("C" + to_string(slotIdSrc), "I" + to_string(slotIdTarget));
                }

                if (temp->isTool()) {
                    cout << "\nItem tidak dipindahkan ke inventory. Terdapat item lain yang sudah berada di inventory.\n\n";
                } else {
                    if (Inventory::buffer[rowTarget][colTarget]->getQuantity() + temp->getQuantity() <= 64) {
                        Inventory::buffer[rowTarget][colTarget]->setQuantity(Inventory::buffer[rowTarget][colTarget]->getQuantity() + temp->getQuantity());
                        Crafting::deleteCraftingSlot(slotIdSrc);
                        cout << "\nItem berhasil dipindahkan dari C" << slotIdSrc << " ke I" << slotIdTarget << ".\n\n";
                    } else {
                        cout << "\nItem tidak dipindahkan ke inventory. Terdapat item lain yang sudah berada di inventory.\n\n";
                    }
                }

            }

        }
    } else {
        string * tempArr= new string[slotQuantity];
        tempArr[0] = inventorySlotIdTarget;

        for (int i = 1; i < slotQuantity; i++) {
            cin >> tempArr[i];
        }

        int failedMove = 0;
        int slotIdTarget;
        int rowSrc = (slotIdSrc / 9), colSrc = (slotIdSrc % 9);

        if (Inventory::buffer[rowSrc][colSrc] == nullptr) {
            throw new ItemNotExistException("I" + to_string(slotIdSrc));
        }

        if (Inventory::buffer[rowSrc][colSrc]->getQuantity() < slotQuantity) {
            throw new NotEnoughItemException("I" + to_string(slotIdSrc));
        }

        Item * temp;
        for (int i = 0; i < slotQuantity; i++) {
            slotIdTarget = stoi(tempArr[i].substr(1));
            temp = Item::createItem(Inventory::buffer[rowSrc][colSrc]->getName(), 1);
            if (Crafting::getCraftingSlot(slotIdTarget) == nullptr) {
                if (temp->isTool()) {
                    ((Tool *)temp)->setDurability(((Tool *)Inventory::buffer[rowSrc][colSrc])->getDurability());
                }

                Crafting::setCraftingSlot(slotIdTarget, temp);
            } else {
                if (temp->getId() == Inventory::buffer[rowSrc][colSrc]->getId()) {
                    if (Crafting::getCraftingSlot(slotIdTarget)->isTool()) {
                        failedMove++;
                    } else {
                        if (temp->getQuantity() + 1 > 64) {
                            failedMove++;
                        } else {
                            Crafting::setCraftingSlot(slotIdTarget, temp);
                        }
                    }
                } else {
                    failedMove++;
                }
            }
        }

        Inventory::buffer[rowSrc][colSrc]->setQuantity(Inventory::buffer[rowSrc][colSrc]->getQuantity() - (slotQuantity - failedMove));
        if (Inventory::buffer[rowSrc][colSrc]->getQuantity() <= 0) {
            delete Inventory::buffer[rowSrc][colSrc];
            Inventory::buffer[rowSrc][colSrc] = nullptr;
        }

        if (failedMove == slotQuantity) {
            cout << "\nItem tidak dapat dimasukkan ke crafting table! (Tidak muat).\n\n";
        } else if (failedMove > 0) {
            cout << "\nItem tidak dipindahkan sepenuhny ke crafting table. Terdapat item lain yang sudah berada di crafting table.\n\n";
        } else {
            cout << "\nItem berhasil dipindahkan.\n\n";
        }

        delete[] tempArr;
    }
}
void Inventory::exportInventory(){

    string targetFile;
    cin >> targetFile;
    ofstream f(targetFile);
    
    for (int i=0; i<27; i++){
        int row = i/9;
        int col = 1 % 9;
        
        if (Inventory::buffer[row][col]==nullptr){
            f<<"0 : 0\n";
        }
        else{
            f << Inventory::buffer[row][col]->getId() << " : ";
            if (Inventory::buffer[row][col]->isTool()) {
                f << ((Tool*)Inventory::buffer[row][col])->getDurability() << endl;
            } else {
                f << Inventory::buffer[row][col]->getQuantity()<<endl;
            }
        }


    }
    f.close();

}

void Inventory::useInventory() {
    string inventorySlotId;
    cin >> inventorySlotId;

    int slotId = stoi(inventorySlotId.substr(1));

    if (slotId < 0 || slotId > 26) {
        throw new NotValidSlotIdException(true);
    }

    int row = slotId / 9, col = slotId % 9;

    if (Inventory::buffer[row][col] == nullptr) {
        throw new ItemNotExistException("I" + to_string(slotId));
    }

    if (!Inventory::buffer[row][col]->isTool()) {
        throw new NonToolUnusableException(slotId);
    }

    ((Tool*)Inventory::buffer[row][col])->useTool();
    cout << "\nTool pada inventori I" << slotId << " digunakan.\n";
    if (((Tool*)Inventory::buffer[row][col])->getDurability() <= 0) {
        cout << "Durability habis, Tool hancur.\n";
        delete Inventory::buffer[row][col];
        Inventory::buffer[row][col] = nullptr;
    }
    cout << '\n';
}

int** Inventory::output() {

    int ** ret = new int*[27];
    Item * temp;
    for (int i = 0; i < 27; i++) {
        ret[i] = new int[2];
    }

    for (int i = 0; i < 27; i++) {
        temp = Inventory::buffer[i / 9][i % 9];
        if (temp != nullptr) {
            ret[i][0] = temp->getId();
            ret[i][1] = temp->isTool() ? ((Tool*)temp)->getDurability() : temp->getQuantity();
        }
        else {
            ret[i][0] = 0;
            ret[i][1] = 0;
        }
    }
    return ret;


}