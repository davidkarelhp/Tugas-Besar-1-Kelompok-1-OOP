#ifndef __NON_TOOL_HPP__
#define __NON_TOOL_HPP__

#include "Item.hpp"

class NonTool : public Item {
    private:

    public:
        NonTool(int id, string name, string type, int quantity);
        
        bool isTool();
};

#endif