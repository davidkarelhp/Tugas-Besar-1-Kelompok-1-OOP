#ifndef __TOOLS_HPP__
#define __TOOLS_HPP__

#include "Item.hpp"

class Tools : public Item {
    private:
        int durability;
    public:
        int getType();
};

#endif