#ifndef __NOT_VALID_SLOT_ID_EXCEPTION_HPP__
#define __NOT_VALID_SLOT_ID_EXCEPTION_HPP__

#include <iostream>
#include "BaseException.hpp"
using namespace std;

class NotValidSlotIdException: public BaseException {
private:
    bool isInventory;
public:

    NotValidSlotIdException(bool isInventory) {
        this->isInventory = isInventory;
    }

    // menuliskan pesan kesalahan ke stdout
    string message() {
        if (this->isInventory) {
            return "Id Slot inventory tidak valid.";
        } else {
            return "Id Slot crafting table tidak valid.";
        }
    }
};

#endif