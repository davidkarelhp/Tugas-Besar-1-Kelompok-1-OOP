#ifndef __TOOL_HPP__
#define __TOOL_HPP__

#include "Item.hpp"

class Tool : public Item {
    private:
        int durability;
    public:
        Tool(int id, string name, string type, int quantity);
        
        int getDurability() const;
        void setDurability(int);
        void useTool();
        bool isTool();
};

#endif