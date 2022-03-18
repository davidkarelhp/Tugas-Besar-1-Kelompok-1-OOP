#ifndef __TOOLS_HPP__
#define __TOOLS_HPP__

#include "Item.hpp"

class Tools : public Item {
    private:
        int durability;
    public:
        Tools(int id, string name, string type, int quantity);
        
        int getDurability() const;
        void useTool();
        //int getType();
};

#endif