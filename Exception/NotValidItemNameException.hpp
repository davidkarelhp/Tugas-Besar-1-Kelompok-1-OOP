#ifndef __NOT_VALID_ITEM_NAME_EXCEPTION_HPP__
#define __NOT_VALID_ITEM_NAME_EXCEPTION_HPP__

#include <iostream>
#include "BaseException.hpp"
using namespace std;

class NotValidItemNameException: public BaseException {
public:
    // menuliskan pesan kesalahan ke stdout
    string message() {
        return "Nama item yang dimasukkan tidak valid! (Tidak ada di file konfigurasi item).";
    }
};

#endif