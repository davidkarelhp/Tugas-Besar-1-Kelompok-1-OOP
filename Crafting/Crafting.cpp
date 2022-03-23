#include "Crafting.hpp"
#include "../Inventory/Inventory.hpp"
#include "../Item/Tool.hpp"

int Crafting::startLeftIdx[2] = {-1, -1};
int Crafting::endLeftIdx[2] = {-1, -1};
int Crafting::startRightIdx[2] = {-1, -1};
int Crafting::endRightIdx[2] = {-1, -1};
int Crafting::filledSlot = 0;
int Crafting::toolsQuantity = 0;

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
    cout << '\n';
}

void Crafting::setCraftingSlot(int slotId, Item * item, bool del) {
    int row = slotId / 3, col = slotId % 3;
    // cout << "start: " << startLeftIdx[0] << " " << startLeftIdx[1] << '\n';
    // cout << "end: " << endLeftIdx[0] << " " << endLeftIdx[1] << '\n';

    if (item != nullptr) {
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
    } else {
        bool found;

        found = false;
        if (row == startLeftIdx[0] && col == startLeftIdx[1]) {
            for (int i = slotId + 1; i < 9 && !found; i++) {
                if (Crafting::craftingTable[i / 3][i % 3] != nullptr) {
                    found = true;
                }
            }

            if (found) {
                startLeftIdx[0] = row;
                startLeftIdx[1] = col;
                found = false;
            } else {
                startLeftIdx[0] = -1;
                startLeftIdx[1] = -1;
            }
        }


        if (row == endLeftIdx[0] && col == endLeftIdx[1]) {
            for (int i = slotId - 1; i >= 9 && !found; i++) {
                if (Crafting::craftingTable[i / 3][i % 3] != nullptr) {
                    found = true;
                }
            }
            if (found) {
                endLeftIdx[0] = row;
                endLeftIdx[1] = col;
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

        for (; i_loop < 3; i_loop++) {
            for (; j_loop >= 0; j_loop--) {
                if (Crafting::craftingTable[i_loop][j_loop] != nullptr) {
                    found = true;
                }
            }
        }

        if (found) {
            endRightIdx[0] = row;
            endRightIdx[1] = col;
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

        for (; i_loop >= 0; i_loop--) {
            for (; j_loop < 0; j_loop++) {
                if (Crafting::craftingTable[i_loop][j_loop] != nullptr) {
                    found = true;
                }
            }
        }

        if (found) {
                startRightIdx[0] = row;
                startRightIdx[1] = col;
                found = false;
            } else {
                startRightIdx[0] = -1;
                startRightIdx[1] = -1;
            }
        }

    }

    if (Crafting::craftingTable[row][col] == nullptr) {
        if (item != nullptr) {
            if (item->isTool()) {
                Crafting::toolsQuantity += 1;
            }
            Crafting::filledSlot += 1;
        }
    } else {
        if (item == nullptr) {
            if (Crafting::craftingTable[row][col]->isTool()) {
                Crafting::toolsQuantity -= 1;
            }
            Crafting::filledSlot -= 1;
        } else {
            if (item->isTool() && !Crafting::craftingTable[row][col]->isTool()) {
                Crafting::toolsQuantity += 1;
            } else if (!item->isTool() && Crafting::craftingTable[row][col]->isTool()) {
                Crafting::toolsQuantity -= 1;
            }
        }
    }

    // cout << Crafting::toolsQuantity << " " << Crafting::filledSlot << "here\n";

    if (Crafting::craftingTable[row][col] != nullptr && del) {
        delete Crafting::craftingTable[row][col];
    }
    
    Crafting::craftingTable[row][col] = item;
    // cout << "start: " << startLeftIdx[0] << " " << startLeftIdx[1] << '\n';
    // cout << "end: " << endLeftIdx[0] << " " << endLeftIdx[1] << '\n';
    // cout << "finish set\n";
}

Item * Crafting::getCraftingSlot(int slotId) {
    int row = slotId / 3, col = slotId % 3;

    return Crafting::craftingTable[row][col];
}

void Crafting::craft() {
    bool found = false;
    int arrLength, idx, i, j, limitj;
    // cout << "start: " << startLeftIdx[0] << " " << startLeftIdx[1] << '\n';
    // cout << "end: " << endLeftIdx[0] << " " << endLeftIdx[1] << '\n';

    if (startLeftIdx[0] != -1) {
        if (Crafting::filledSlot == 2 && Crafting::filledSlot == Crafting::toolsQuantity) {
            if (Crafting::craftingTable[Crafting::startLeftIdx[0]][Crafting::startLeftIdx[1]]->getId() == Crafting::craftingTable[Crafting::endLeftIdx[0]][Crafting::endLeftIdx[1]]->getId()) {
                cout << "\nItem yang di-craft adalah " << Crafting::craftingTable[Crafting::startLeftIdx[0]][Crafting::startLeftIdx[1]]->getName() << " dengan durability " << min(10, 
                    ((Tool*)Crafting::craftingTable[Crafting::startLeftIdx[0]][Crafting::startLeftIdx[1]])->getDurability() +
                    ((Tool*)Crafting::craftingTable[Crafting::endLeftIdx[0]][Crafting::endLeftIdx[1]])->getDurability()) << ".\n";
                Inventory::giveAlgorithm(Crafting::craftingTable[Crafting::startLeftIdx[0]][Crafting::startLeftIdx[1]]->getName(), 1, 
                    min(10, 
                    ((Tool*)Crafting::craftingTable[Crafting::startLeftIdx[0]][Crafting::startLeftIdx[1]])->getDurability() +
                    ((Tool*)Crafting::craftingTable[Crafting::endLeftIdx[0]][Crafting::endLeftIdx[1]])->getDurability()
                ));
                // cout << ((Tool*)Crafting::craftingTable[Crafting::startLeftIdx[0]][Crafting::startLeftIdx[1]])->getDurability() << " " << ((Tool*)Crafting::craftingTable[Crafting::endLeftIdx[0]][Crafting::endLeftIdx[1]])->getDurability() << '\n';
                Crafting::clear();

            } else {
                cout << "\nTidak ada resep yang cocok dengan konfigurasi item pada crafting table.\n\n";
            }
        } else {
            string * arr;
            Triplet<string, int , int> * temp = new Triplet<string, int , int>;
            if (startLeftIdx[0] != endLeftIdx[0]) {
                arrLength = (endLeftIdx[0] - startLeftIdx[0] + 1) * 3 - startLeftIdx[1];
                limitj = 2;
            } else  {
                arrLength = (endLeftIdx[0] * 3 + endLeftIdx[1]) - (startLeftIdx[0] * 3 + startLeftIdx[1]) + 1;
                limitj = endLeftIdx[1];
            }

            arr = new string[arrLength];

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
                    } else {
                        arr[idx] = Crafting::craftingTable[i][j]->getName();
                    }
                    idx++;
                }
            }

            // cout << "\narrLength: " << arrLength << '\n';
            // for (int k = 0; k < arrLength; k++) {
            //     cout << arr[k] << " ";
            // }
            // cout << "\n\n";

            temp = Crafting::trie.checkRecipe(arr, arrLength, endLeftIdx[0] - startLeftIdx[0] + 1);

            if (temp != nullptr) {
                found = true;
            } 

            delete[] arr;

            if (!found) {

                if (startLeftIdx[0] != endLeftIdx[0]) {
                    arrLength = (endLeftIdx[0] - startLeftIdx[0] + 1) * 3 - (2 - startRightIdx[1]);
                    limitj = 0;
                } else  {
                    arrLength = (endRightIdx[0] * 3 + (2 - endRightIdx[1])) - (startRightIdx[0] * 3 + (2 - startRightIdx[1])) + 1;
                    limitj = endRightIdx[1];
                }
                arr = new string[arrLength];

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

            if (!found) {
                cout << "\nTidak ada resep yang cocok dengan konfigurasi item pada crafting table.\n\n";
            } else {
                cout << "\nItem yang di-craft adalah " << temp->getFirst() << " dengan jumlah " << temp->getSecond() << ".\n";
                Inventory::giveAlgorithm(temp->getFirst(), temp->getSecond(), 0);
                delete temp;
                Crafting::clear();
            }
        }
    }
    // cout << "start: " << startLeftIdx[0] << " " << startLeftIdx[1] << '\n';
    // cout << "end: " << endLeftIdx[0] << " " << endLeftIdx[1] << '\n';
}

void Crafting::deleteCraftingSlot(int slotId) {
    // cout << "start: " << startLeftIdx[0] << " " << startLeftIdx[1] << '\n';
    // cout << "end: " << endLeftIdx[0] << " " << endLeftIdx[1] << '\n';
    int row = slotId / 3, col = slotId % 3, i;
    // cout << "row: " << row << ", col: " << col << '\n';

    if (Crafting::craftingTable[row][col] != nullptr) {
        if (Crafting::craftingTable[row][col]->isTool()) {
            Crafting::toolsQuantity -= max (0, Crafting::toolsQuantity - 1);
        }
        Crafting::filledSlot -= max (0, Crafting::filledSlot - 1);

        bool found;

        found = false;
        if (row == startLeftIdx[0] && col == startLeftIdx[1]) {
            // cout << "here\n";
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

    }

    delete Crafting::craftingTable[row][col];
    Crafting::craftingTable[row][col] = nullptr;
    // cout << "start: " << startLeftIdx[0] << " " << startLeftIdx[1] << '\n';
    // cout << "end: " << endLeftIdx[0] << " " << endLeftIdx[1] << '\n';
}

void Crafting::clear() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (Crafting::craftingTable[i][j] != nullptr) {
                delete Crafting::craftingTable[i][j];
                Crafting::craftingTable[i][j] = nullptr;
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
    Crafting::filledSlot = 0;
    Crafting::toolsQuantity = 0;
}