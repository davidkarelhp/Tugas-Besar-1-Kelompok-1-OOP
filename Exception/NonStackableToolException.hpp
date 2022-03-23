#ifndef __NON_STACKABLE_TOOL_EXCEPTION_HPP__
#define __NON_STACKABLE_TOOL_EXCEPTION_HPP__

#include <iostream>
#include "BaseException.hpp"
using namespace std;

class NonStackableToolException: public BaseException {
public:
    // menuliskan pesan kesalahan ke stdout
    string message() {
        return "Item bertipe Tool tidak dapat ditumpuk.";
    }
};

#endif