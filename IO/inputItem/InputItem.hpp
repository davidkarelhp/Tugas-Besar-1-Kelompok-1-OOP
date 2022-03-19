#ifndef __INPUT_ITEM_HPP__
#define __INPUT_ITEM_HPP__

#include "../../Item/Item.hpp"

enum ItemAttributes {
	id,
	name,
	type,
	tool
};
class InputItem {
    public:
        static void readLine(string);
        static void readFile(string);
};


#endif