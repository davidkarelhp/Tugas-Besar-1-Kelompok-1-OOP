#ifndef __DIFFERENT_ITEM_EXCEPTION_HPP__
#define __DIFFERENT_ITEM_EXCEPTION_HPP__

#include <iostream>
#include "BaseException.hpp"
using namespace std;

class DifferentItemException: public BaseException {
private:
    string loc1, loc2;
public:

    DifferentItemException(string loc1, string loc2) {
        this->loc1 = loc1;
        this->loc2 = loc2;
    }

    string message() {
        return "Item pada " + this->loc1 + " dan " + this->loc2 + " tidak sama.";
    }


};

#endif