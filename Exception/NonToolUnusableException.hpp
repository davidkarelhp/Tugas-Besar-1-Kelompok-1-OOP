#ifndef __NON_TOOL_UNUSABLE_EXCEPTION_HPP__
#define __NON_TOOL_UNUSABLE_EXCEPTION_HPP__

#include <iostream>
#include "BaseException.hpp"
using namespace std;

class NonToolUnusableException: public BaseException {
private:
    int loc;
public:

    NonToolUnusableException(int loc) {
        this->loc = loc;
    }

    // menuliskan pesan kesalahan ke stdout
    string message() {
        return "Item pada inventori I" + to_string(this->loc) + " tidak bertipe Tool sehingga tidak dapat digunakan.";
    }
};

#endif