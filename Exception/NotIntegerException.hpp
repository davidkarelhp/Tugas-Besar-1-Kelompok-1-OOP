#ifndef __NOT_INTEGER_EXCEPTION_HPP__
#define __NOT_INTEGER_EXCEPTION_HPP__

#include <iostream>
#include "BaseException.hpp"
using namespace std;

class NotIntegerException: public BaseException {
public:
    string message() {
        return "Masukkan integer (bilangan bulat)!";
    }
};

#endif