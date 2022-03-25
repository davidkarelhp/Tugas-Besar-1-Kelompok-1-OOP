#include "Crafting.hpp"
#include "../Inventory/Inventory.hpp"
#include "../Item/Tool.hpp"

int Crafting::startLeftIdx[2] = {-1, -1};
int Crafting::endLeftIdx[2] = {-1, -1};
int Crafting::startRightIdx[2] = {-1, -1};
int Crafting::endRightIdx[2] = {-1, -1};
int Crafting::filledSlot = 0;
int Crafting::toolsQuantity = 0;
int Crafting::minQuantity = 0;

RecipeTrie Crafting::trie = RecipeTrie();

Item * Crafting::craftingTable[3][3] = {{nullptr, nullptr, nullptr}, {nullptr, nullptr, nullptr}, {nullptr, nullptr, nullptr}};

void Crafting::showCraftingTable() {
    cout << "CRAFTING TABLE\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (craftingTable[i][j] == nullptr) {
                cout << "[-1 00]";
            } else {
                int id = Crafting::craftingTable[i][j]->getId();
                int quantity = Crafting::craftingTable[i][j]->getQuantity();
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
    Triplet<string, int, int> * temp;

    temp = Crafting::checkCraftingConfiguration();

    if (temp == nullptr) {
        cout << "HASIL CRAFTING: -\n";
    } else {
        cout << "HASIL CRAFTING: " << temp->getFirst() << " dengan jumlah " << temp->getSecond() * Crafting::minQuantity << '\n';
    }
    cout << '\n';
}

void Crafting::setCraftingSlot(int slotId, Item * item) {
    int row = slotId / 3, col = slotId % 3, quantity;

    if (Crafting::craftingTable[row][col] == nullptr) {
        if (startLeftIdx[0] == -1) {
            startLeftIdx[0] = row;
            startLeftIdx[1] = col;
            startRightIdx[0] = row;
            startRightIdx[1] = col;
            endLeftIdx[0] = row;
            endLeftIdx[1] = col;
            endRightIdx[0] = row;
            endRightIdx[1] = col;

        } else {
            if (row < startLeftIdx[0]) {
                startLeftIdx[0] = row;
                startLeftIdx[1] = col;
                startRightIdx[0] = row;
                startRightIdx[1] = col;

            } else if (row == startLeftIdx[0]) {
                if (startLeftIdx[1] > col) {
                    startLeftIdx[1] = col;
                }

                if (startRightIdx[1] < col) {
                    startRightIdx[1] = col;
                }
            }

            if (row > endLeftIdx[0]) {
                endLeftIdx[0] = row;
                endLeftIdx[1] = col;
                endRightIdx[0] = row;
                endRightIdx[1] = col;

            } else if (row == endLeftIdx[0]) {
                if (endLeftIdx[1] < col) {
                    endLeftIdx[1] = col;
                }

                if (endRightIdx[1] > col) {
                    endRightIdx[1] = col;
                }
            }
        }

        if (item->isTool()) {
            Crafting::toolsQuantity += 1;
        }
        Crafting::filledSlot += 1;
        Crafting::craftingTable[row][col] = item;
        Crafting::minQuantity = 1;
    } else {
        if (item->getId() == Crafting::craftingTable[row][col]->getId()) {
            Crafting::craftingTable[row][col]->setQuantity(Crafting::craftingTable[row][col]->getQuantity() + 1);
        }
        quantity = Crafting::craftingTable[row][col]->getQuantity() + 1;

        if (Crafting::craftingTable[row][col]->getQuantity() - 1 == Crafting::minQuantity) {
            bool found = false;
            int i, j, tempMin;

            tempMin = 100;

            for (i = startLeftIdx[0] * 3 + startLeftIdx[1]; i < 9; i++) {
                if (Crafting::craftingTable[i / 3][i % 3] != nullptr) {
                    found = true;
                    if (Crafting::craftingTable[i / 3][i % 3]->getQuantity() < tempMin) {
                        tempMin = Crafting::craftingTable[i / 3][i % 3]->getQuantity();
                    }
                }
            }

            Crafting::minQuantity = found ? tempMin : 0;
        }
        delete item;
    }
    
}

Item * Crafting::getCraftingSlot(int slotId) {
    int row = slotId / 3, col = slotId % 3;

    return Crafting::craftingTable[row][col];
}

void Crafting::craft() {
    bool found = false;
    int arrLength, idx, i, j, limitj;

    if (startLeftIdx[0] != -1) {
        if (Crafting::filledSlot == 2 && Crafting::filledSlot == Crafting::toolsQuantity) {
            if (Crafting::craftingTable[Crafting::startLeftIdx[0]][Crafting::startLeftIdx[1]]->getId() == Crafting::craftingTable[Crafting::endLeftIdx[0]][Crafting::endLeftIdx[1]]->getId()) {

                cout << R"(
 / ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \
 |  /~~\                                                       /~~\  |
 |\ \   |   ____                                    _  _  _   |   / /|
 | \   /|  / ___|  _   _   ___  ___  ___  ___  ___ | || || |  |\   / |
 |  ~~  |  \___ \ | | | | / __|/ __|/ _ \/ __|/ __|| || || |  |  ~~  |
 |      |   ___) || |_| || (__| (__|  __/\__ \\__ \|_||_||_|  |      |
 |      |  |____/  \__,_| \___|\___|\___||___/|___/(_)(_)(_)  |      |
 |      |                                                     |      |
  \     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|     /
   \   /                                                       \   /
    ~~~                                                         ~~~              
                )" << endl;

                cout << "\nItem yang di-craft adalah " << Crafting::craftingTable[Crafting::startLeftIdx[0]][Crafting::startLeftIdx[1]]->getName() << " dengan durability " << min(10, 
                    ((Tool*)Crafting::craftingTable[Crafting::startLeftIdx[0]][Crafting::startLeftIdx[1]])->getDurability() +
                    ((Tool*)Crafting::craftingTable[Crafting::endLeftIdx[0]][Crafting::endLeftIdx[1]])->getDurability()) << ".\n";
                Inventory::giveAlgorithm(Crafting::craftingTable[Crafting::startLeftIdx[0]][Crafting::startLeftIdx[1]]->getName(), 1, 
                    min(10, 
                    ((Tool*)Crafting::craftingTable[Crafting::startLeftIdx[0]][Crafting::startLeftIdx[1]])->getDurability() +
                    ((Tool*)Crafting::craftingTable[Crafting::endLeftIdx[0]][Crafting::endLeftIdx[1]])->getDurability()
                ));

                Crafting::clear(Crafting::minQuantity);

            } else {
                cout << "\nTidak ada resep yang cocok dengan konfigurasi item pada crafting table.\n\n";
            }
        } else {
            Triplet<string, int, int> * temp = new Triplet<string, int , int>;
            temp = Crafting::checkCraftingConfiguration();
            if (temp == nullptr) {
                cout << "\nTidak ada resep yang cocok dengan konfigurasi item pada crafting table.\n\n";
            } else {
                cout << R"(
 / ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \
 |  /~~\                                                       /~~\  |
 |\ \   |   ____                                    _  _  _   |   / /|
 | \   /|  / ___|  _   _   ___  ___  ___  ___  ___ | || || |  |\   / |
 |  ~~  |  \___ \ | | | | / __|/ __|/ _ \/ __|/ __|| || || |  |  ~~  |
 |      |   ___) || |_| || (__| (__|  __/\__ \\__ \|_||_||_|  |      |
 |      |  |____/  \__,_| \___|\___|\___||___/|___/(_)(_)(_)  |      |
 |      |                                                     |      |
  \     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|     /
   \   /                                                       \   /
    ~~~                                                         ~~~              
                )" << endl;

                cout << "\nItem yang di-craft adalah " << temp->getFirst() << " dengan jumlah " << temp->getSecond() * Crafting::minQuantity << ".\n";
                Inventory::giveAlgorithm(temp->getFirst(), temp->getSecond() * Crafting::minQuantity, 0);
                Crafting::clear(Crafting::minQuantity);
            }
        }
    }
}

Triplet<string, int, int> * Crafting::checkCraftingConfiguration() {
    string * arr;
    bool found;
    int limitj, arrLength, idx, i, j;
    Triplet<string, int , int> * temp;
    limitj = endLeftIdx[1];
    arrLength = (endLeftIdx[0] * 3 + endLeftIdx[1]) - (startLeftIdx[0] * 3 + startLeftIdx[1]) + 1;

    arr = new string[arrLength + 2];

    idx = 0;
    for (i = startLeftIdx[0]; i <= endLeftIdx[0]; i++) {
        if (i == startLeftIdx[0]) {
            j = startLeftIdx[1];
        } else {
            j = 0;
        }

        for (; (j < 3 && i != endLeftIdx[0]) || j <= limitj; j++) {
            if (Crafting::craftingTable[i][j] == nullptr) {
                arr[idx] = "-";

            } 
            else {
                arr[idx] = Crafting::craftingTable[i][j]->getName();
                if (j > limitj) {
                    limitj = j;
                    arrLength++;
                }
            }
            idx++;
        }
    }

    temp = Crafting::trie.checkRecipe(arr, arrLength, endLeftIdx[0] - startLeftIdx[0] + 1);

    if (temp != nullptr) {
        found = true;
    } 

    delete[] arr;

    if (!found) {
        limitj = endRightIdx[1];
        arrLength = (endRightIdx[0] * 3 + (2 - endRightIdx[1])) - (startRightIdx[0] * 3 + (2 - startRightIdx[1])) + 1;
        arr = new string[arrLength + 2];

        idx = 0;

        for (i = startRightIdx[0]; i <= endRightIdx[0]; i++) {
            if (i == startRightIdx[0]) {
                j = startRightIdx[1];
            } else {
                j = 2;
            }

            for (; (j >= 0 && i != endRightIdx[0]) || j >= limitj; j--) {
                if (Crafting::craftingTable[i][j] == nullptr) {
                    arr[idx] = "-";
                } else {
                    arr[idx] = Crafting::craftingTable[i][j]->getName();
                    if (j < limitj) {
                        limitj = j;
                        arrLength++;
                    }
                }

                idx++;
            }
        }

        temp = Crafting::trie.checkRecipe(arr, arrLength, endRightIdx[0] - startRightIdx[0] + 1);

        if (temp != nullptr) {
            found = true;
        } 
    
        delete[] arr;
    }

    return temp;

    
}

void Crafting::deleteCraftingSlot(int slotId) {
    int row = slotId / 3, col = slotId % 3, i;

    if (Crafting::craftingTable[row][col] != nullptr) {
        if (Crafting::craftingTable[row][col]->isTool()) {
            Crafting::toolsQuantity -= max (0, Crafting::toolsQuantity - 1);
        }
        Crafting::filledSlot -= max (0, Crafting::filledSlot - 1);

        bool found;

        found = false;
        if (row == startLeftIdx[0] && col == startLeftIdx[1]) {
            for (i = slotId + 1; i < 9 && !found; i++) {
                if (Crafting::craftingTable[i / 3][i % 3] != nullptr) {
                    found = true;
                }
            }

            if (found) {
                startLeftIdx[0] = (i - 1) / 3;
                startLeftIdx[1] = (i - 1) % 3;
                found = false;
            } else {
                startLeftIdx[0] = -1;
                startLeftIdx[1] = -1;
            }
        }


        if (row == endLeftIdx[0] && col == endLeftIdx[1]) {
            for (i = slotId - 1; i >= 9 && !found; i++) {
                if (Crafting::craftingTable[i / 3][i % 3] != nullptr) {
                    found = true;
                }
            }
            if (found) {
                endLeftIdx[0] = (i - 1) / 3;
                endLeftIdx[1] = (i - 1) % 3;
                found = false;

            } else {
                endLeftIdx[0] = -1;
                endLeftIdx[1] = -1;

            }
        }


        if (row == startRightIdx[0] && col == startRightIdx[1]) {
            int i_loop, j_loop;
            if (row % 3 == 2) {
                i_loop = row - 1;
                i_loop = 0;
            } else {
                i_loop = row;
                j_loop = col + 1;
            }

            for (; i_loop < 3 && !found; i_loop++) {
                for (; j_loop >= 0 && !found; j_loop--) {
                    if (Crafting::craftingTable[i_loop][j_loop] != nullptr) {
                        found = true;
                    }
                }
            }

            if (found) {
                endRightIdx[0] = i_loop - 1;
                endRightIdx[1] = j_loop + 1;
                found = false;
            } else {
                endRightIdx[0] = -1;
                endRightIdx[1] = -1;
            }
        }

        if (row == endRightIdx[0] && col == endRightIdx[1]) {
            int i_loop, j_loop;
            if (row % 3 == 2) {
                i_loop = row - 1;
                j_loop = 0;
            } else {
                i_loop = row;
                j_loop = col + 1;
            }

            for (; i_loop >= 0 && !found; i_loop--) {
                for (; j_loop < 0 && !found; j_loop++) {
                    if (Crafting::craftingTable[i_loop][j_loop] != nullptr) {
                        found = true;
                    }
                }
            }

            if (found) {
                startRightIdx[0] = i_loop + 1;
                startRightIdx[1] = j_loop - 1;
                found = false;
            } else {
                startRightIdx[0] = -1;
                startRightIdx[1] = -1;
            }
        }
        if (Crafting::craftingTable[row][col]->getQuantity() == Crafting::minQuantity) {
            bool found = false;
            int i, j, tempMin;

            tempMin = 100;

            for (i = startLeftIdx[0] * 3 + startLeftIdx[1]; i < 9; i++) {
                if (Crafting::craftingTable[i / 3][i % 3] != nullptr) {
                    found = true;
                    if (Crafting::craftingTable[i / 3][i % 3]->getQuantity() < tempMin) {
                        tempMin = Crafting::craftingTable[i / 3][i % 3]->getQuantity();
                    }
                }
            }

            Crafting::minQuantity = found ? tempMin : 0;
        }

        delete Crafting::craftingTable[row][col];
        Crafting::craftingTable[row][col] = nullptr;

    }

}

void Crafting::clear(int delQuantity) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (Crafting::craftingTable[i][j] != nullptr) {
                Crafting::craftingTable[i][j]->setQuantity(Crafting::craftingTable[i][j]->getQuantity() - delQuantity);
                if (Crafting::craftingTable[i][j]->getQuantity() <= 0) {
                    if (Crafting::craftingTable[i][j]->isTool()) {
                        Crafting::toolsQuantity--;
                    }
                    Crafting::filledSlot--;
                    delete Crafting::craftingTable[i][j];
                    Crafting::craftingTable[i][j] = nullptr;
                }
            }
        }
    }
    startLeftIdx[0] = -1;
    startLeftIdx[1] = -1;
    endLeftIdx[0] = -1;
    endLeftIdx[1] = -1;
    startRightIdx[0] = -1;
    startRightIdx[1] = -1;
    endRightIdx[0] = -1;
    endRightIdx[1] = -1;
    bool found1 = false, found2 = false;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (Crafting::craftingTable[i][j] != nullptr) {
                if (!found1) {
                    startLeftIdx[0] = i;
                    startLeftIdx[1] = j;
                    endLeftIdx[0] = i;
                    endLeftIdx[1] = j;
                    found1 = true;
                } else {
                    if (i > endLeftIdx[0]) {
                        endLeftIdx[0] = i;
                        endLeftIdx[1] = j;
                    } else if (i == endLeftIdx[0] && j > endLeftIdx[1]) {
                        endLeftIdx[1] = j;
                    }
                }
            }
        }

        for (int j = 2; j >= 0; j--) {
            if (Crafting::craftingTable[i][j] != nullptr) {
                if (!found2) {
                    startRightIdx[0] = i;
                    startRightIdx[1] = j;
                    endRightIdx[0] = i;
                    endRightIdx[1] = j;
                    found2 = true;
                } else {
                    if (i > endRightIdx[0]) {
                        endRightIdx[0] = i;
                        endRightIdx[1] = j;
                    } else if (i == endRightIdx[0] && j < endRightIdx[1]) {
                        endRightIdx[1] = j;
                    }
                }
            }
        }
    }
}