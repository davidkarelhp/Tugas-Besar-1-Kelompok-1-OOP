#ifndef __TRIPLET_HPP__
#define __TRIPLET_HPP__

#include <iostream>

class Triplet {
    private:
        int id;
        std::string typeItem;
        bool tool;
    public:
        Triplet();
        Triplet(int id, std::string typeItem, bool tool);
        int getId();
        std::string getTypeItem();
        bool isTool();

};

#endif