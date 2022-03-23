#ifndef __NOT_ENOUGH_ITEM_EXCEPTION_HPP__
#define __NOT_ENOUGH_ITEM_EXCEPTION_HPP__

#include <iostream>
#include "BaseException.hpp"
using namespace std;

class NotEnoughItemException: public BaseException {
private:
    string loc;
public:

    NotEnoughItemException(string loc) {
        this->loc = loc;
    }

    // menuliskan pesan kesalahan ke stdout
    string message() {
        return "Item pada " + this->loc + " tidak mencukupi.";
    }
};

#endif