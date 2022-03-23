#ifndef __ITEM_NOT_EXIST_EXCEPTION_HPP__
#define __ITEM_NOT_EXIST_EXCEPTION_HPP__

#include <iostream>
#include "BaseException.hpp"
using namespace std;

class ItemNotExistException: public BaseException {
private:
    string loc;
public:

    ItemNotExistException(string loc) {
        this->loc = loc;
    }

    // menuliskan pesan kesalahan ke stdout
    string message() {
        return "Tidak ada item pada " + this->loc;
    }
};

#endif